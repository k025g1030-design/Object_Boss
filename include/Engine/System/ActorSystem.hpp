#pragma once

namespace Engine::System {
    class ActorSystem {
    public:
        ActorSystem() = default;
        ~ActorSystem() = default;
        void Update(float dt);
        void Render();
    };

}