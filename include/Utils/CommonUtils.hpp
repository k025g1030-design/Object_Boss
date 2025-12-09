#pragma once
#include <string>


namespace Utils {
    class Common {
    public:
        static unsigned int Color(int r, int g, int b, int a) {
            return ((a & 0xff) << 24) |
                ((b & 0xff) << 16) |
                ((g & 0xff) << 8) |
                (r & 0xff);
        }

        // 色にアルファ値を合成する ()
        static unsigned int ColorWithAlpha(unsigned int color, float alpha) {
            alpha = std::clamp(alpha, 0.0f, 1.0f);
            unsigned int a = static_cast<unsigned int>(alpha * 255.0f);
            return (color & 0xffffff00) | a;
        }


    };
}
