#pragma once
#include "Engine/System/GameSession.hpp"
#include "Engine/System/Camera.hpp"
#include "Engine/Asset/Data/AnimationData.hpp"

namespace Engine::System {

    class ActorSystem {
    public:
        void Initialize(Engine::System::GameSession* session);
        void Update(float dt);
        void Render(Camera camera);

    private:
        Engine::System::GameSession* session_ = nullptr;

    private:
        Engine::Asset::AnimationData* playerAnime_ = nullptr;
        Engine::Asset::AnimationData* bossAnime_ = nullptr;
        float animTime_ = 0;
        int currentIndex_ = 0;

    };

}