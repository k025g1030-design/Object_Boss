#pragma once
#include <string>


namespace Utils {
    class Common {
    public:
        static unsigned int Color(int r, int g, int b, int a) {
            return ((a & 0xff) << 24) | ((b & 0xff) << 16) | ((g & 0xff) << 8) | (r & 0xff);
        }

        static unsigned int ColorWithAlpha(unsigned int color, float alpha) {
            if (alpha < 0.0f) alpha = 0.0f;
            if (alpha > 1.0f) alpha = 1.0f;
            unsigned int a = static_cast<unsigned int>(alpha * 255.0f) & 0xff;
            return (color & 0x00ffffff) | (a << 24);
        }


    };
}
