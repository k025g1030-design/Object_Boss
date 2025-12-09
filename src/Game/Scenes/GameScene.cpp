#include "Game/Scenes/GameScene.hpp"
#include "Engine/Scene/SceneChangeContext.hpp"


namespace Game::Scenes {
    void GameScene::InitializeContext(const Engine::Scene::SceneChangeContext& ctx) {
        currentLevelId_ = ctx.Get("levelId", "data.level.00");

        levelData_ = Engine::GetCore().GetAssetManager().Load<Engine::Asset::LevelData>(currentLevelId_);
        mapData_ = Engine::GetCore().GetAssetManager().Load<Engine::Asset::MapData>(levelData_->mapAssetId);
        Engine::GetCore().GetMapSystem().Initialize(mapData_);
    }

    void GameScene::OnEnter() {
        // シーンに入ったときの初期化処理をここに追加
    }
    void GameScene::OnExit() {
        // シーンを出るときのクリーンアップ処理をここに追加
    }
    void GameScene::OnPause() {

    }
    void GameScene::OnResume() {

    }
    void GameScene::Update() {
        // ゲームシーンの更新処理をここに追加
    }
    void GameScene::Render() {
        // ゲームシーンの描画処理をここに追加
        //Engine::RenderText({ 50, 50 }, "Game Scene: " + currentLevelId_);
        
        Engine::GetCore().GetMapSystem().RenderLayer("floor", camera_);
        Engine::GetCore().GetMapSystem().RenderLayer("road", camera_);
        Engine::GetCore().GetMapSystem().RenderLayer("trigger", camera_);
        Engine::GetCore().GetMapSystem().RenderLayer("wall", camera_);
        // Render player and actors here

        Engine::GetCore().GetMapSystem().RenderLayer("portal", camera_);
        


    }
} // namespace Scene
