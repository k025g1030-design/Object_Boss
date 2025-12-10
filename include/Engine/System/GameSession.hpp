#pragma once
#include "Entity/Player.hpp"
#include "Entity/Enemy.hpp"
#include "Engine/System/Camera.hpp"

namespace Engine::System {
    struct GameSession {
        Entity::Player player;
        Entity::Enemy enemy;
        bool isGameClear = false;
        bool isExit = false;
        
    };
}
