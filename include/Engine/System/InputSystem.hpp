#pragma once
#include "Core/Math.hpp"

namespace Engine::System {
    class InputSystem {
    public:
        void Poll();
        void Update(float speed);
        Core::Vector2 GetInputSnapshot() const { return inputSnapshot_; }
        Core::Vector2 GetVelocity() const { return velocity_; }
        bool GetShoot() { return shoot_; }
        void SetShoot(bool shoot) { shoot_ = shoot; }

    private:
        Core::Vector2 inputSnapshot_{ 0.0f, 0.0f };
        Core::Vector2 velocity_{ 0.0f, 0.0f };
        bool shoot_{false};
    };

}
