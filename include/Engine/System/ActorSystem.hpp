#pragma once
#include "Engine/System/GameSession.hpp"
#include "Engine/System/Camera.hpp"
#include "Engine/Asset/Data/AnimationData.hpp"
#include "Engine/Asset/Data/TileSetData.hpp"
#include "TriggerPool.hpp"

namespace Engine::System {

    class ActorSystem {
    public:
        void Initialize(Engine::System::GameSession* session);
        void Update(float dt);
        void MovePlayer(Core::Vector2 delta);
        void MoveEnemy();
        void PlayAnime(float dt);
        void Render(Camera camera);
        void ReadTriggerHits();
        void Shoot();

        std::vector<TriggerHit> ConsumeTriggerHits() {
            std::vector<TriggerHit> out;
            out.swap(triggerHits_);   // O(1) swap
            return out;
        }

    private:
        Engine::System::GameSession* session_ = nullptr;
        std::vector<TriggerHit> triggerHits_;

    private:
        Engine::Asset::AnimationData* playerAnime_ = nullptr;
        Engine::Asset::AnimationData* bossAnime_ = nullptr;
        Engine::Asset::TileSetData* tileset_ = nullptr;
        float animTime_ = 0;
        int currentIndex_ = 0;

    };

}