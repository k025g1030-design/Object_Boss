#pragma once

namespace Engine::Scene {
    class IScene {
    public:
        virtual ~IScene() = default;
        virtual void OnEnter() = 0;
        virtual void OnExit() = 0;

        virtual void Update() = 0;
        virtual void Render() = 0;
    };

}