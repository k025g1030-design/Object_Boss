#include "Game/Scenes/OverScene.hpp"
#include "Engine/Scene/SceneChangeContext.hpp"




namespace Game::Scenes {
    void OverScene::InitializeContext(const Engine::Scene::SceneChangeContext& ctx) {
        result_ = ctx.Get("result", "win");
        guiData_ = Engine::GetCore().GetAssetManager().Load<Engine::Asset::TileSetData>("data.tileset.ui");
    }
    void OverScene::OnEnter() {
        // シーンに入ったときの初期化処理をここに追加
        enterButton_ = Component::Button({ 160, 30 }, { Core::kWindowWidth / 2 - 80, Core::kWindowHeight / 2 + 340 }, "RETURN");
    }
    void OverScene::OnExit() {
        // シーンを出るときのクリーンアップ処理をここに追加
    }
    void OverScene::OnPause() {

    }
    void OverScene::OnResume() {

    }
    void OverScene::Update() {
        // メニューシーンの更新処理をここに追加
        bool mouseDown = Engine::MouseLeftClicked();
        int moX = 0;
        int moY = 0;
        Engine::GetMousePosition(&moX, &moY);
        if (enterButton_.HandleMouse(moX, moY, mouseDown, prevMouseDown_)) {
            Engine::Scene::SceneChangeContext ctx;
            Engine::GetCore().GetSceneManager().ChangeSceneWithFade("ui.menu", ctx);
        }
        prevMouseDown_ = mouseDown;
    }
    void OverScene::Render() {
        // メニューシーンの描画処理をここに追加
        if (result_ == "win") {
            Engine::RenderTile({ 0, 0 }, guiData_, "over.win");
        } else {
            Engine::RenderTile({ 0, 0 }, guiData_, "over.lose");
        }
        enterButton_.Render();
        
    }
} // namespace Scene

