#pragma once
#include "Engine/Scene/IScene.hpp"

namespace Scenes {
    class GameScene : public IScene {
    public:
        void OnEnter() override;
        void OnExit() override;
        void Update() override;
        void Render() override;
    private:
        // メニューシーン固有のメンバ変数をここに追加
    };
}