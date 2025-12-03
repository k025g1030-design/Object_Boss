#pragma once
#include "Engine/Scene/IScene.hpp"
#include "Engine/Scene/SceneManager.hpp"
#include "Engine/Asset/AssetsManager.hpp"



namespace Scene {

    class MenuScene : public IScene {
    public:
        explicit MenuScene(SceneManager& scenes, Asset::AssetManager& assets) : scenes_(scenes), assets_(assets) {};
        ~MenuScene() override = default;

        void OnEnter() override;
        void OnExit() override;
        void Update() override;
        void Render() override;
    private:
        SceneManager& scenes_;
        Asset::AssetManager& assets_
        //InputSystem& inputSystem_;
    };
}