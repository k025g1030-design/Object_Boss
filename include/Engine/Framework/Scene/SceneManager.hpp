#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "Engine/Framework/Scene/IScene.hpp"

namespace Scene {
    /**
     シーン管理クラス
     - シーンの切り替えや管理を担当
    **/
    class SceneManager {
    public:
        explicit SceneManager() = default;
        ~SceneManager() = default;

        void ChangeScene(const std::string& sceneId);

        void Update(float dt);
        void Render();

    private:
        // id : Scene
        std::unordered_map<std::string, std::shared_ptr<IScene>> scenes;
        IScene* current = nullptr;
    };
} // namespace Engine
