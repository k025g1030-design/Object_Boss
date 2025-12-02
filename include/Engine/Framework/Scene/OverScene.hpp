#pragma once
#include "Engine/Framework/Scene/IScene.hpp"

namespace Scene {
    class OverScene : public IScene {
    public:
        void OnEnter() override;
        void OnExit() override;
        void Update() override;
        void Render() override;
    private:
        // メニューシーン固有のメンバ変数をここに追加
    };
}