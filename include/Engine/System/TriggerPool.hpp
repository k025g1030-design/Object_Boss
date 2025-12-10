#pragma once
#include <string>


namespace Engine::System {
    struct TriggerHit {
        int actorId;            // 或指標、enum，先簡單用 int
        std::string triggerId;  // "skill.to_sui", "portal.to_boss_room" 等
    };

}
