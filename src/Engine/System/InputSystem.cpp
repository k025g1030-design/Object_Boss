#include "Engine/System/InputSystem.hpp"
#include "Core/Backend.hpp"

namespace Engine::System {
    void InputSystem::Poll() {
        // 初期化処理があればここに記述
        if (Engine::Backend::CheckHitKey(DIK_W)) {
            inputSnapshot_.y = 1.0f;
        } else if (Engine::Backend::CheckHitKey(DIK_S)) {
            inputSnapshot_.y = -1.0f;
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
    }
    void InputSystem::Update(float speed) {
        // フレームごとの入力状態更新処理があればここに記述
        double angle = atan2(inputSnapshot_.y, inputSnapshot_.x);
        velocity_ = {
            static_cast<float>(cos(angle) * speed),
            static_cast<float>(sin(angle) * speed)
        };
    }


}