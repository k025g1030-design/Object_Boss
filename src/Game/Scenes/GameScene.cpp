#include "Game/Scenes/GameScene.hpp"
#include "Engine/Scene/SceneChangeParam.hpp"

namespace Game::Scenes {
    void GameScene::InitializeContext(const Engine::Scene::SceneChangeParam& param) {
        currentLevelId_ = param.Get("levelId", "data.level.00");
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
    }
} // namespace Scene
