#pragma once
#include <memory>
#include <string>
#include <vector>
#include "Engine/Scene/MetaData/SceneMeta.hpp"
#include "Engine/Scene/IScene.hpp"

namespace Engine::Scene {

    class SceneFactory;
    class SceneRegistry; 

    class SceneManager {
    public:
        SceneManager() = default;

        void Initialize(SceneRegistry& registry, SceneFactory& factory);

        // シーン切り替え API
        void ChangeScene(const std::string& sceneId); // スタックをクリアして、新しいシーンを読み込む
        void PushScene(const std::string& sceneId);   // シーンを上に重ねる（overlay）
        void PopScene();                              // 最上位（トップ）のシーンを取り除く

        void Update(float dt);
        void Render();

        bool IsEmpty() const { return sceneStack_.empty(); }

    private:
        // 内部ツール
        void ClearStack_();
        std::unique_ptr<IScene> CreateSceneById_(const std::string& sceneId);
        const SceneDef* GetSceneDef_(const std::string& sceneId) const;

    private:
        SceneRegistry* registry_ = nullptr;
        SceneFactory* factory_ = nullptr;

        // スタックの底 = index 0、頂点 = back()
        std::vector<std::unique_ptr<IScene>> sceneStack_;
    };

} // namespace Engine::Scene
