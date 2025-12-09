#pragma once
#include "Engine/Scene/IScene.hpp"
#include "Core/EngineAPI.hpp"
#include "Engine/System/Camera.hpp"
#include <Entity/Player.hpp>
#include <Entity/Enemy.hpp>

namespace Game::Scenes {
    struct GameSession {
        Entity::Player player;
        Entity::Enemy enemy;
        Engine::System::Camera camera;
    };
    

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

    private:
        // メニューシーン固有のメンバ変数をここに追加
        std::string currentLevelId_;
        Engine::Asset::LevelData* levelData_ = nullptr;
        Engine::Asset::MapData* mapData_ = nullptr;
        
        GameSession session_;
        
    };
}