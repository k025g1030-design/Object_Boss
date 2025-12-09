#pragma once
#include "Engine/System/GameSession.hpp"

namespace Engine::System {
    class GuiSystem {
    public:
        GuiSystem() = default;
        ~GuiSystem() = default;
        void Initialize(Engine::System::GameSession* session);
        void Update(float dt);
        void Render();
    private:
        Engine::System::GameSession* session_ = nullptr;

    };

}
