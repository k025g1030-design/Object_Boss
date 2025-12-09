#include "Game/Scenes/OverScene.hpp"
#include "Engine/Scene/SceneChangeContext.hpp"


namespace Game::Scenes {
    void OverScene::InitializeContext(const Engine::Scene::SceneChangeContext& ctx) {
        result_ = ctx.Get("result", "win");
    }
    void OverScene::OnEnter() {
        // シーンに入ったときの初期化処理をここに追加
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
    }
    void OverScene::Render() {
        // メニューシーンの描画処理をここに追加
    }
} // namespace Scene

