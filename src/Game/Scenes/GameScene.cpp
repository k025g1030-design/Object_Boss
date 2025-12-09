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
        int unit = mapData_->tileset->scale.pixelsPerUnit;
        session_.player.SetPosition({ (float)(levelData_->player.spawn.x * unit), (float)(levelData_->player.spawn.y * unit) });
        session_.player.SetSize({ 50.0f, 50.0f });
        session_.player.SetHP(Entity::PLAYER_MAX_HP);
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
        Core::Vector2 velocity = Engine::GetCore().GetInputSystem().GetVelocity();
        session_.player.SetPosition(session_.player.GetPosition() + velocity);

        UpdateCameraWithDeadZone(session_.player, session_.camera);
        session_.camera;
    }
    void GameScene::Render() {
        // ゲームシーンの描画処理をここに追加
        //Engine::RenderText({ 50, 50 }, "Game Scene: " + currentLevelId_);
        
        
        Engine::GetCore().GetMapSystem().RenderLayer("floor", session_.camera);
        Engine::GetCore().GetMapSystem().RenderLayer("wall", session_.camera);
        Engine::GetCore().GetMapSystem().RenderLayer("road", session_.camera);
        //Engine::GetCore().GetMapSystem().RenderLayer("trigger", camera_);
        //Engine::GetCore().GetMapSystem().RenderLayer("wall", camera_);

        
        Engine::GetCore().GetMapSystem().RenderDecorationsNotKey("portal", session_.camera);

        //// Render player and actors here
        session_.player.Draw(session_.camera);
        Engine::GetCore().GetMapSystem().RenderDecorationsInKey("portal", session_.camera);

        

        //// Render UI elements here
        


    }


    // 假設：
// - 世界座標左上為 (0,0)
// - camera.x, camera.y = 畫面左上在世界中的座標
// - player.x, player.y = 玩家中心的世界座標
// - mapPixelWidth, mapPixelHeight = 整張地圖的像素大小 (map.width * tileSize, map.height * tileSize)

    void GameScene::UpdateCameraWithDeadZone(const Entity::Player& player, Engine::System::Camera& camera) {
        int mapPixelWidth = mapData_->width * mapData_->tileset->scale.pixelsPerUnit;
        int mapPixelHeight = mapData_->height * mapData_->tileset->scale.pixelsPerUnit;

        // 1. 玩家在螢幕上的位置（螢幕左上為 (0,0)）
        int screenX = static_cast<int>(player.GetPosition().x) - camera.x;
        int screenY = static_cast<int>(player.GetPosition().y) - camera.y;

        // 2. 橫向：檢查是否超出死區
        if (screenX < camera.deadLeft) {
            // 玩家太靠左 → 把相機往左推，直到玩家剛好在 deadLeft
            camera.x = static_cast<int>(player.GetPosition().x) - camera.deadLeft;
        } else if (screenX > camera.deadRight) {
            // 玩家太靠右 → 把相機往右推
            camera.x = static_cast<int>(player.GetPosition().x) - camera.deadRight;
        }

        // 3. 縱向：檢查是否超出死區
        if (screenY < camera.deadTop) {
            camera.y = static_cast<int>(player.GetPosition().y) - camera.deadTop;
        } else if (screenY > camera.deadBottom) {
            camera.y = static_cast<int>(player.GetPosition().y) - camera.deadBottom;
        }

        // 4. 相機不要滑出地圖外（用地圖像素大小來 clamp）
        int maxCamX = mapPixelWidth - camera.viewportWidth;
        int maxCamY = mapPixelHeight - camera.viewportHeight;
        if (maxCamX < 0) maxCamX = 0;
        if (maxCamY < 0) maxCamY = 0;

        if (camera.x < 0)       camera.x = 0;
        if (camera.y < 0)       camera.y = 0;
        if (camera.x > maxCamX) camera.x = maxCamX;
        if (camera.y > maxCamY) camera.y = maxCamY;
    }

} // namespace Scene
