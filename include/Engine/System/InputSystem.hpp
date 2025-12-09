#pragma once
#include "Core/Math.hpp"

namespace Engine::System {
    class InputSystem {
    public:
        InputSystem() = default;
        ~InputSystem() = default;
        void Poll();
        void Update(float speed);
        Core::Vector2 GetInputSnapshot() const { return inputSnapshot_; }
        Core::Vector2 GetVelocity() const { return velocity_; }

    private:
        Core::Vector2 inputSnapshot_{ 0.0f, 0.0f };
        Core::Vector2 velocity_{ 0.0f, 0.0f };
    };

}
