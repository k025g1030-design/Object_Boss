#pragma once
#include "Engine/Scene/IScene.hpp"
#include "Core/EngineAPI.hpp"
#include "Component/Button.hpp"

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
    public:
        void InitializeContext(const Engine::Scene::SceneChangeContext& /*ctx*/) override {}

    private:                                                    
        Engine::Asset::TileSetData* guiData_ = nullptr;
        bool prevMouseDown_{ false };

    private:
        Component::Button startButton_;
        Component::Button continueButton_;
        Component::Button readmeButton_;
        Component::Button exitButton_;
    };

} // namespace Game::Scenes