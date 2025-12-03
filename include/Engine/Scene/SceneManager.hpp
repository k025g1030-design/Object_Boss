#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "Engine/Scene/IScene.hpp"

namespace Engine::Scene {
    /**
     シーン管理クラス
     - シーンの切り替えや管理を担当
    **/
    class SceneManager {
    public:
        explicit SceneManager() = default;
        ~SceneManager() = default;

        void Register(const std::string& sceneId, std::shared_ptr<IScene> scene);

        void ChangeScene(const std::string& sceneId);

        void Update(float dt);
        void Render();

    private:
        // id : Scene
        std::unordered_map<std::string, std::shared_ptr<IScene>> scenes_;
        IScene* current_ = nullptr;
    };
} // namespace Engine
