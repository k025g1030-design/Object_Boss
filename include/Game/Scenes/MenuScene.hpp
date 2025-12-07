#pragma once
#include "Engine/Scene/IScene.hpp"
#include "Core/EngineAPI.hpp"

namespace Game::Scenes {

    class MenuScene : public Engine::Scene::IScene {
    public:
        explicit MenuScene() = default;
        ~MenuScene() = default;

        void OnEnter() override;
        void OnExit() override;
        void OnPause() override;
        void OnResume() override;
        void Update() override;
        void Render() override;
    private:
        //Engine::Scene::SceneManager& scenes_;
        //Engine::Asset::AssetManager& assets_;
        //InputSystem& inputSystem_;
    };
}