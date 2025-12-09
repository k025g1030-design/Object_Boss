#pragma once

namespace Engine::System {
    class GuiSystem {
    public:
        GuiSystem() = default;
        ~GuiSystem() = default;
        void Update(float dt);
        void Render();
    private:
    };

}
