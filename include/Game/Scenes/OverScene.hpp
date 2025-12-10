#pragma once
#include "Engine/Scene/IScene.hpp"
#include "Core/EngineAPI.hpp"
#include "Component/Button.hpp"

namespace Game::Scenes {

    class OverScene : public Engine::Scene::IScene {
    public:
        ~OverScene() = default;
        void OnEnter() override;
        void OnExit() override;
        void OnPause() override;
        void OnResume() override;
        void Update() override;
        void Render() override;
    public:
        void InitializeContext(const Engine::Scene::SceneChangeContext& ctx) override;

    private:
        Component::Button enterButton_;
        bool prevMouseDown_;

    private:
        // メニューシーン固有のメンバ変数をここに追加
        std::string result_;
        Engine::Asset::TileSetData* guiData_ = nullptr;

    };
}