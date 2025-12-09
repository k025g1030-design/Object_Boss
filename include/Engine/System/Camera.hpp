#pragma once
#include "Core/Config.hpp"

namespace Engine::System {

    struct Camera {
        int x = 0;
        int y = 0;
        int viewportWidth = Core::kWindowWidth;
        int viewportHeight = Core::kWindowHeight;

        int deadLeft;
        int deadRight;
        int deadTop;
        int deadBottom;

        Camera()
            : deadLeft((Core::kWindowWidth - Core::DEAD_ZONE_W) / 2),
            deadRight(Core::kWindowWidth - ((Core::kWindowWidth - Core::DEAD_ZONE_W) / 2)),     // kWindowWidth - deadLeft
            deadTop((Core::kWindowHeight - Core::DEAD_ZONE_H) / 2),
            deadBottom(Core::kWindowHeight - ((Core::kWindowHeight - Core::DEAD_ZONE_H) / 2)) {    // kWindowHeight - deadTop
        }

        
    };
}
