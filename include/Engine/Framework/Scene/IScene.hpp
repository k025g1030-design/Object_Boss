#pragma once

namespace Scene {
    class IScene {
    public:
        virtual ~IScene() = default;
		virtual void OnEnter() = 0; // 初期化
		virtual void Update() = 0;  // 更新
		virtual void Render() = 0;  // 描画
		virtual void OnExit() = 0;  // 終了
    };
}