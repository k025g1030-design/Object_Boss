#pragma once
#include "Engine/Scene/IScene.hpp"
#include "Engine/Scene/SceneManager.hpp"
#include "Engine/Asset/AssetsManager.hpp"



namespace Game::Scenes {

    class MenuScene : public Engine::Scene::IScene {
    public:
        //explicit MenuScene(Engine::Scene::SceneManager& scenes, Engine::Asset::AssetManager& assets) : scenes_(scenes), assets_(assets) {};
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