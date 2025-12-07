#include "Engine/Scene/SceneManager.hpp"
#include "Engine/Scene/IScene.hpp"
#include "Engine/Scene/SceneFactory.hpp"

#include "Engine/Scene/MetaData/SceneMeta.hpp"
#include "Engine/Scene/SceneRegistry.hpp"

#include <cassert>

namespace Engine::Scene {

    void SceneManager::Initialize(SceneRegistry& registry, SceneFactory& factory) {
        registry_ = &registry;
        factory_ = &factory;
    }

    const SceneDef* SceneManager::GetSceneDef_(const std::string& sceneId) const {
        assert(registry_ && "SceneManager not initialized: registry is null");
        return registry_->Get(sceneId);   
    }

    std::unique_ptr<IScene> SceneManager::CreateSceneById_(const std::string& sceneId) {
        const SceneDef* def = GetSceneDef_(sceneId);
        if (!def) {
            assert(false && "SceneManager: sceneId not found in registry");
            return nullptr;
        }
        assert(factory_ && "SceneManager not initialized: factory is null");
        return factory_->Create(*def);
    }

    void SceneManager::ClearStack_() {
        // 從頂到底依序 OnExit
        for (auto it = sceneStack_.rbegin(); it != sceneStack_.rend(); ++it) {
            (*it)->OnExit();
        }
        sceneStack_.clear();
    }

    // ---------------- 重要：ChangeScene 行為 ----------------
    // ChangeScene = 「旧シーンをクリアし、新しいシーンに切り替える」
    // 元のスタックを保持せず、排他的（exclusive）な切り替えを行う。
    void SceneManager::ChangeScene(const std::string& sceneId) {
        auto newScene = CreateSceneById_(sceneId);
        if (!newScene) return;

        ClearStack_();

        newScene->OnEnter();
        sceneStack_.push_back(std::move(newScene));
    }

    // PushScene = 「既存のシーンの上にさらに重ねる」
    // 例：GameScene の上に PauseScene を重ねる
    void SceneManager::PushScene(const std::string& sceneId) {
        auto newScene = CreateSceneById_(sceneId);
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
        dt; // 未使用
        if (sceneStack_.empty()) return;

        // 更新は最上位シーンだけを行う
        sceneStack_.back()->Update();
    }

    void SceneManager::Render() {
        if (sceneStack_.empty()) return;

        // 描画は下から順に行い、下層シーンが見えるようにする（例：Pause の半透明マスク）
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
                ChangeScene(targetDef->sceneId);
                // TODO: levelId が指定されていればレベルをセット
                // GameScene.SetStartLevel(trans->levelId);

            } else {
                // overlay でシーンを重ねる
                PushScene(targetDef->sceneId);
            }
        }

        
    }
} // namespace Engine::Scene
