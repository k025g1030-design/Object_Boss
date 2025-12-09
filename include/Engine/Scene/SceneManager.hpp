
#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Engine/Scene/MetaData/SceneMeta.hpp"
#include "Engine/Scene/IScene.hpp"
#include "Engine/Scene/SceneChangeContext.hpp"

namespace Engine::Scene {

    enum class SceneTransitPhase {
        None,       // トランジションなし
        FadeOut,    // 旧シーンをフェードアウト
        SwitchScene,// シーン切り替え ＋ Level / Map の読み込み
        FadeIn      // 新シーンをフェードイン
    };

    struct SceneTransitState {
        SceneTransitPhase phase = SceneTransitPhase::None;

        std::string targetSceneId;
        SceneChangeContext ctx;   

        float timer = 0.0f;
        float fadeOutDuration = 0.5f;
        float fadeInDuration = 0.5f;
    };



    class SceneFactory;
    class SceneRegistry; 

    class SceneManager {
    public:
        SceneManager() = default;
        void Initialize(std::shared_ptr<SceneRegistry> registry, std::shared_ptr<SceneFactory> factory);
        void HandleEvent(const std::string& sceneId, const std::string& eventId);
        bool IsEmpty() const { return sceneStack_.empty(); }
        
    public:
        // シーン切り替え API , スタックをクリアして、新しいシーンを読み込む
        void ChangeScene(const std::string& sceneId, const SceneChangeContext& ctx = {}); // 
        // シーン切り替え API , フェードアウト・フェードイン付き
        void ChangeSceneWithFade(const std::string& sceneId, const SceneChangeContext& ctx = {}, 
            float fadeOut = 0.5f,
            float fadeIn = 0.5f
        );
        void PushScene(const std::string& sceneId, const SceneChangeContext& ctx = {});   // シーンを上に重ねる（overlay）
        void PopScene();                              // 最上位（トップ）のシーンを取り除く
        void Update(float dt);
        void Render();

    private:
        // 内部ツール
        void ClearStack_();
        std::unique_ptr<IScene> CreateSceneById_(const std::string& sceneId, SceneChangeContext ctx);
        const SceneDef* GetSceneDef_(const std::string& sceneId) const;

    private:
        // スタックの底 = index 0、頂点 = back()
        std::vector<std::unique_ptr<IScene>> sceneStack_;
        SceneTransitState sceneTransit_;

    private:
        std::shared_ptr<SceneRegistry> registry_ = nullptr;
        std::shared_ptr<SceneFactory> factory_ = nullptr;
    };
} // namespace Engine::Scene
