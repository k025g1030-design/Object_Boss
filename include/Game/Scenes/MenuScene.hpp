#pragma once
#include "Engine/Scene/IScene.hpp"
#include "Engine/Scene/SceneManager.hpp"
#include "Engine/Asset/AssetsManager.hpp"



namespace Scenes {

    class MenuScene : public Scene::IScene {
    public:
        explicit MenuScene(Scene::SceneManager& scenes, Asset::AssetManager& assets) : scenes_(scenes), assets_(assets) {};
        ~MenuScene() override = default;

        void OnEnter() override;
        void OnExit() override;
        void Update() override;
        void Render() override;
    private:
        Scene::SceneManager& scenes_;
        Asset::AssetManager& assets_;
        //InputSystem& inputSystem_;
    };
}