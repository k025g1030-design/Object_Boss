#include "Engine/Scene/SceneManager.hpp"
#include "Engine/Scene/IScene.hpp"
#include "Engine/Scene/SceneFactory.hpp"

#include "Engine/Scene/MetaData/SceneMeta.hpp"
#include "Engine/Scene/SceneRegistry.hpp"
#include "Utils/CommonUtils.hpp"
#include "Core/EngineAPI.hpp"

#include <cassert>

namespace Engine::Scene {

    void SceneManager::Initialize(std::shared_ptr<SceneRegistry> registry, std::shared_ptr<SceneFactory> factory) {
        registry_ = registry;
        factory_ = factory;
    }

    const SceneDef* SceneManager::GetSceneDef_(const std::string& sceneId) const {
        assert(registry_ && "SceneManager not initialized: registry is null");
        return registry_->Get(sceneId);   
    }

    std::unique_ptr<IScene> SceneManager::CreateSceneById_(const std::string& sceneId, SceneChangeContext ctx) {
        const SceneDef* def = GetSceneDef_(sceneId);
        if (!def) {
            assert(false && "SceneManager: sceneId not found in registry");
            return nullptr;
        }
        assert(factory_ && "SceneManager not initialized: factory is null");
        return factory_->Create(*def, ctx);
    }

    void SceneManager::ClearStack_() {
        // トップからボトムへ順に OnExit を呼び出す
        for (auto it = sceneStack_.rbegin(); it != sceneStack_.rend(); ++it) {
            (*it)->OnExit();
        }
        sceneStack_.clear();
    }

    // ---------------- 重要：ChangeScene 行為 ----------------
    // ChangeScene = 「旧シーンをクリアし、新しいシーンに切り替える」
    // 元のスタックを保持せず、排他的（exclusive）な切り替えを行う。
    void SceneManager::ChangeScene(const std::string& sceneId, const SceneChangeContext& ctx) {
        auto newScene = CreateSceneById_(sceneId, ctx);
        if (!newScene) return;

        ClearStack_();

        newScene->OnEnter();
        sceneStack_.push_back(std::move(newScene));
    }

    void SceneManager::ChangeSceneWithFade(const std::string& sceneId,
        const SceneChangeContext& ctx,
        float fadeOut,
        float fadeIn) {
        sceneTransit_.phase = SceneTransitPhase::FadeOut;
        sceneTransit_.targetSceneId = sceneId;
        sceneTransit_.ctx = ctx;
        sceneTransit_.timer = 0.0f;
        // TODO: JSON からデフォルト値を取得するように変更
        sceneTransit_.fadeOutDuration = fadeOut;
        sceneTransit_.fadeInDuration = fadeIn;
    }


    // PushScene = 「既存のシーンの上にさらに重ねる」
    // 例：GameScene の上に PauseScene を重ねる
    void SceneManager::PushScene(const std::string& sceneId, const SceneChangeContext& ctx) {
        auto newScene = CreateSceneById_(sceneId, ctx);
        if (!newScene) return;

        if (!sceneStack_.empty()) {
            // 現在の最上位シーンへ「覆われた」ことを通知する
            sceneStack_.back()->OnPause();
        }

        newScene->OnEnter();
        sceneStack_.push_back(std::move(newScene));
    }

    // PopScene = 最上位のシーンを取り除く
    void SceneManager::PopScene() {
        if (sceneStack_.empty()) return;

        // 1. トップのシーンを削除
        auto& top = sceneStack_.back();
        top->OnExit();
        sceneStack_.pop_back();

        // 2. 新しいトップのシーンがあれば、そのシーンを「復帰」させる
        if (!sceneStack_.empty()) {
            sceneStack_.back()->OnResume();
        }
    }

    // ---------------- Update / Render スタックのロジック ----------------

    void SceneManager::Update(float dt) {
        if (dt == 0.0f){
            dt = 1.0f / 60.0f; 
        }
        // 1.トランジション中でなければ → 最上位シーンだけを更新する
        if (sceneTransit_.phase == SceneTransitPhase::None) {
            if (!sceneStack_.empty()) {
                sceneStack_.back()->Update();
            }
            return;
        }

        // 2.トランジション中の場合
        switch (sceneTransit_.phase) {
        case SceneTransitPhase::FadeOut:
            sceneTransit_.timer += dt;
            if (sceneTransit_.timer >= sceneTransit_.fadeOutDuration) {
                sceneTransit_.timer = 0.0f;
                sceneTransit_.phase = SceneTransitPhase::SwitchScene;
            }

            /**
             * FadeOut 期間 
             * [x] あるいは旧シーンを更新する（アニメーションを動かし続ける）
             * [ ] 更新しない（画面は静止し、黒フェードだけが進む）
             **/
            if (!sceneStack_.empty()) {
                sceneStack_.back()->Update();
            }
            break;

        case SceneTransitPhase::SwitchScene:
            // Point：ここで実際のシーン切り替え ＋ Level / Map の読み込みを行う
        {
            auto newScene = CreateSceneById_(
                sceneTransit_.targetSceneId,
                sceneTransit_.ctx
            );
            if (newScene) {
                ClearStack_();
                // → GameScene::OnEnter() 内で Level / Map をロードする
                newScene->OnEnter();   
                sceneStack_.push_back(std::move(newScene));
            }
        }
        sceneTransit_.phase = SceneTransitPhase::FadeIn;
        sceneTransit_.timer = 0.0f;
        break;

        case SceneTransitPhase::FadeIn:
            sceneTransit_.timer += dt;
            // FadeIn 中は新しいシーンを通常どおり更新する
            if (!sceneStack_.empty()) {
                sceneStack_.back()->Update();
            }
            if (sceneTransit_.timer >= sceneTransit_.fadeInDuration) {
                sceneTransit_.timer = 0.0f;
                sceneTransit_.phase = SceneTransitPhase::None;
            }
            break;

        default:
            break;
        }
    }

    void SceneManager::Render() {
        if (sceneStack_.empty()) return;

        // temp: 描画は下から順に行い、下層シーンが見えるようにする（例：Pause の半透明マスク）
        /*for (auto& s : sceneStack_) {
            s->Render();
        }*/

        /*
          SceneDef.renderUnderlay 制御
          SceneDef.renderUnderlay に従って下層描画を制御する場合、
          上から逆順に走査し、最初に renderUnderlay == false のシーンに到達した時点で描画を止める
        */
        int startIndex = static_cast<int>(sceneStack_.size()) - 1;
        for (int i = startIndex; i >= 0; --i) {
            const IScene* s = sceneStack_[i].get();
            const SceneDef* def = GetSceneDef_(s->GetSceneId());
            if (!def || !def->stackBehavior.renderUnderlay) {
                startIndex = i;
                break;
            }
        }

        // startIndex から頂点まで順にレンダー(Render)する
        for (int i = startIndex; i < static_cast<int>(sceneStack_.size()); ++i) {
            sceneStack_[i]->Render();
        }


        if (sceneTransit_.phase == SceneTransitPhase::None) {
            return;
        }

        float alpha = 0.0f;

        if (sceneTransit_.phase == SceneTransitPhase::FadeOut) {
            float t = sceneTransit_.timer / sceneTransit_.fadeOutDuration;
            if (t > 1.0f) t = 1.0f;
            alpha = t;                // 0 → 1：だんだん黒くなる（フェードアウト）
        } else if (sceneTransit_.phase == SceneTransitPhase::FadeIn) {
            float t = sceneTransit_.timer / sceneTransit_.fadeInDuration;
            if (t > 1.0f) t = 1.0f;
            alpha = 1.0f - t;         // 1 → 0：黒幕がゆっくり消えていく（フェードイン）
        } else if (sceneTransit_.phase == SceneTransitPhase::SwitchScene) {
            alpha = 1.0f;            // 中間のわずかなフレームで、完全な黒にしてしまってもよい
        }

        // DrawFullScreenQuad with alpha
        // TODO: renderSystem を取得して描画する
        Engine::RenderFullScreenQuad(Utils::Common::ColorWithAlpha(0x000000, alpha));

    }

    void SceneManager::HandleEvent(const std::string& sceneId, const std::string& eventId) {
        if (sceneStack_.empty()) return;

        const SceneDef* def = GetSceneDef_(sceneId);
        if (!def) return;

        const TransitionDef* trans = nullptr;
        for (auto& t : def->transitions) {
            if (t.eventId == eventId) {
                trans = &t;
                break;
            }
        }
        if (!trans) return;

        // event: "exit" → targetScene == null → 
        if (trans->targetSceneId) {
            // targetSceneId が指定されていない場合、ゲーム終了
            // TODO: ゲーム終了処理
            // g_shouldQuit = true;  //Game::Quit();
            return;
        } else {
            const SceneDef* targetDef = GetSceneDef_(trans->targetSceneId.value());
            if (!targetDef) return;

            if (targetDef->stackBehavior.mode == StackBehaviorMode::Exclusive) {
                // go to 新しいシーンへ完全切り替え
                //ChangeScene(targetDef->sceneId);
                // TODO: levelId が指定されていればレベルをセット
                // GameScene.SetStartLevel(trans->levelId);
                SceneChangeContext ctx;
                if (trans->levelId.has_value()) {
                    ctx.Set("levelId", trans->levelId.value());
                }
                ChangeSceneWithFade(targetDef->sceneId, ctx);
            } else {
                // overlay でシーンを重ねる
                PushScene(targetDef->sceneId);
            }
        }

        
    }
} // namespace Engine::Scene
