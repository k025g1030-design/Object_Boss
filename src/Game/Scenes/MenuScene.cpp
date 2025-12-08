#include "Game/Scenes/MenuScene.hpp"

namespace Game::Scenes {
    void MenuScene::OnEnter() {
        // シーンに入ったときの初期化処理をここに追加
        guiData_ = Engine::GetCore().GetAssetManager().Load<Engine::Asset::TileSetData>("data.tileset.ui");
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
    }
    void MenuScene::Render() {
        // メニューシーンの描画処理をここに追加

        Engine::RenderTile({0,0}, guiData_, "menu.bg");

        Engine::RenderTile({ 100, 140 }, guiData_, "menu.title.text");

        Engine::RenderTileBtn({ Core::kWindowWidth /2 -80, Core::kWindowHeight / 2 + 140}, guiData_, "menu.opt.start");

        Engine::RenderTileBtn({ Core::kWindowWidth / 2 - 80, Core::kWindowHeight / 2 + 180}, guiData_, "menu.opt.continue");

        Engine::RenderTileBtn({ Core::kWindowWidth / 2 - 80, Core::kWindowHeight / 2 + 220}, guiData_, "menu.opt.readme");

        Engine::RenderTileBtn({ Core::kWindowWidth / 2 - 80, Core::kWindowHeight / 2 + 260}, guiData_, "menu.opt.exit");
        
    }
} // namespace Scene
