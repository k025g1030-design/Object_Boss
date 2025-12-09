#pragma once

namespace Core {
    inline constexpr const char* kWindowTitle = "Object_Boss「荒神」";
    inline constexpr const int kWindowWidth = 832;         // 13 * 64
    inline constexpr const int kWindowHeight = 768;        // 12 * 64
    inline constexpr const int PIXELS_PER_UNIT = 64;

    inline constexpr float kPi = 3.1415926535f;
    inline constexpr int DEAD_ZONE_W = 7 * PIXELS_PER_UNIT;
    inline constexpr int DEAD_ZONE_H = 6 * PIXELS_PER_UNIT;

    enum MouseButton {
        LEFT_BUTTON = 0,
        RIGHT_BUTTON = 1,
        MIDDLE_BUTTON = 2,
    };
}
