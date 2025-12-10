#pragma once
#include "Engine/Scene/IScene.hpp"
#include "Core/EngineAPI.hpp"
#include "Engine/System/Camera.hpp"
#include "Engine/System/GameSession.hpp"
#include "Engine/System/TriggerPool.hpp"

namespace Game::Scenes {
    class GameScene : public Engine::Scene::IScene {
    public:
        ~GameScene() = default;
        void OnEnter() override;
        void OnExit() override;
        void OnPause() override;
        void OnResume() override;
        void Update() override;
        void Render() override;

    public:
        void InitializeContext(const Engine::Scene::SceneChangeContext& ctx) override;
        void UpdateCameraWithDeadZone(const Entity::Player& player, Engine::System::Camera& camera);
        void HandleTrigger(const Engine::System::TriggerHit& hit);

    private:
        // メニューシーン固有のメンバ変数をここに追加
        std::string currentLevelId_;
        Engine::Asset::LevelData* levelData_ = nullptr;
        Engine::Asset::MapData* mapData_ = nullptr;
        
        Engine::System::GameSession session_;
        Engine::System::Camera camera_;
        
    };
}