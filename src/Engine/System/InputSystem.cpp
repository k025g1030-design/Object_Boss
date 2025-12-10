#include "Engine/System/InputSystem.hpp"
#include "Core/Backend.hpp"

namespace Engine::System {
    void InputSystem::Poll() {
        // 初期化処理があればここに記述
        if (Engine::Backend::CheckHitKey(DIK_W)) {
            inputSnapshot_.y = -1.0f;
        } else if (Engine::Backend::CheckHitKey(DIK_S)) {
            inputSnapshot_.y = 1.0f;
        } else {
            inputSnapshot_.y = 0.0f;
        }

        if (Engine::Backend::CheckHitKey(DIK_D)) {
            inputSnapshot_.x = 1.0f;
        } else if (Engine::Backend::CheckHitKey(DIK_A)) {
            inputSnapshot_.x = -1.0f;
        } else {
            inputSnapshot_.x = 0.0f;
        }

        if (Engine::Backend::CheckHitKey(DIK_SPACE)) {
            shoot_ = true;
        }
    }
    void InputSystem::Update(float speed) {
        // フレームごとの入力状態更新処理があればここに記述
        if ((int)inputSnapshot_.y != 0 || (int)inputSnapshot_.x != 0) {
            double angle = atan2(inputSnapshot_.y, inputSnapshot_.x);
            velocity_ = {
                static_cast<float>(cos(angle) * speed),
                static_cast<float>(sin(angle) * speed)
            };
        } else {
            velocity_ = { 0.0f, 0.0f };
        }
    }


}