#include "Game/Scenes/MenuScene.hpp"
#include <cstdlib>


namespace Game::Scenes {

    void MenuScene::OnEnter() {
        // シーンに入ったときの初期化処理をここに追加
        guiData_ = Engine::GetCore().GetAssetManager().Load<Engine::Asset::TileSetData>("data.tileset.ui");

        startButton_ = Component::Button({ 160, 30 }, { Core::kWindowWidth / 2 - 80, Core::kWindowHeight / 2 + 140 }, "");
        continueButton_ = Component::Button({ 160, 30 }, { Core::kWindowWidth / 2 - 80, Core::kWindowHeight / 2 + 180 }, "");
        readmeButton_ = Component::Button({ 160, 30 }, { Core::kWindowWidth / 2 - 80, Core::kWindowHeight / 2 + 220 }, "");
        exitButton_ = Component::Button({ 160, 30 }, { Core::kWindowWidth / 2 - 80, Core::kWindowHeight / 2 + 260 }, "");
    }
    void MenuScene::OnExit() {
        // シーンを出るときのクリーンアップ処理をここに追加
    }
    void MenuScene::OnPause() {

    }
    void MenuScene::OnResume() {

    }
    void MenuScene::Update() {
        // メニューシーンの更新処理をここに追加
        bool mouseDown = Engine::MouseLeftClicked();
        int moX = 0;
        int moY = 0;
        Engine::GetMousePosition(&moX, &moY);
        if (startButton_.HandleMouse(moX, moY, mouseDown, prevMouseDown_)) {
            Engine::Scene::SceneChangeContext ctx;
            ctx.Set("levelId", "data.level.00");
            Engine::GetCore().GetSceneManager().ChangeSceneWithFade("game.main", ctx);
        } else if (continueButton_.HandleMouse(moX, moY, mouseDown, prevMouseDown_)) {
            Engine::Scene::SceneChangeContext ctx;
            ctx.Set("levelId", "data.level.01");
            Engine::GetCore().GetSceneManager().ChangeSceneWithFade("game.main", ctx);
        } else if (readmeButton_.HandleMouse(moX, moY, mouseDown, prevMouseDown_)) {
            // Engine::GetCore().GetSceneManager().ChangeSceneWithFade("ui.over");
        } else if (exitButton_.HandleMouse(moX, moY, mouseDown, prevMouseDown_)) {
            // Exit
            std::exit(0);
        }
        prevMouseDown_ = mouseDown;

    }
    void MenuScene::Render() {
        // メニューシーンの描画処理をここに追加

        Engine::RenderTile({0,0}, guiData_, "menu.bg");

        Engine::RenderTile({ 100, 140 }, guiData_, "menu.title.text");

        startButton_.Render();
        Engine::RenderTile(startButton_.GetPosition(), guiData_, "menu.opt.start");

        continueButton_.Render();
        Engine::RenderTile(continueButton_.GetPosition(), guiData_, "menu.opt.continue");

        readmeButton_.Render();
        Engine::RenderTile(readmeButton_.GetPosition(), guiData_, "menu.opt.readme");

        exitButton_.Render();
        Engine::RenderTile(exitButton_.GetPosition(), guiData_, "menu.opt.exit");
        
    }
} // namespace Scene
