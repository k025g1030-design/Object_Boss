#pragma once
#include <math.h>
#include <string>

namespace Core {

    class Vector2 {
    public:
        float x{ 0.0f };
        float y{ 0.0f };

        Vector2() = default;
        Vector2(float _x, float _y) : x(_x), y(_y) {}

        Vector2 operator+(const Vector2& o) const { return { x + o.x, y + o.y }; }
        Vector2 operator-(const Vector2& o) const { return { x - o.x, y - o.y }; }
        Vector2& operator+=(const Vector2& o) { x += o.x; y += o.y; return *this; }
        Vector2& operator-=(const Vector2& o) { x -= o.x; y -= o.y; return *this; }
    };
    class VectorInt2 {
    public:
        int x{ 0 };
        int y{ 0 };

        VectorInt2() = default;
        VectorInt2(int _x, int _y) : x(_x), y(_y) {}

        VectorInt2 operator+(const VectorInt2& o) const { return { x + o.x, y + o.y }; }
        VectorInt2 operator-(const VectorInt2& o) const { return { x - o.x, y - o.y }; }
        VectorInt2& operator+=(const VectorInt2& o) { x += o.x; y += o.y; return *this; }
        VectorInt2& operator-=(const VectorInt2& o) { x -= o.x; y -= o.y; return *this; }
    };

    class Matrix2x2 {
    public:
        float m[2][2]{ { 0.0f, 0.0f }, { 0.0f, 0.0f } };
        Matrix2x2() = default;

        Vector2 operator*(const Vector2& o) const {
            Vector2 result = { 0, 0 };
            result.x = o.x * m[0][0] - o.y * m[1][0];
            result.y = o.x * m[0][1] + o.y * m[1][1];
            return result;
        }

        Matrix2x2 MakeRotateMatrix(float theta) {
            Matrix2x2 result = {};
            for (int row = 0; row < 2; ++row) {
                for (int col = 0; col < 2; ++col) {
                    if (row == col) {
                        result.m[row][col] = cosf(theta);
                    } else {
                        result.m[row][col] = sinf(theta);
                    }
                }
            }
            return result;
        }
    };

    class Point {
    public:
        Vector2 leftTop;
        Vector2 rightTop;
        Vector2 leftBottom;
        Vector2 rightBottom;

        Point operator+(const Vector2& o) const {
            Point result;
            result.leftTop = { leftTop.x + o.x, leftTop.y + o.y };
            result.rightTop = { rightTop.x + o.x, rightTop.y + o.y };
            result.leftBottom = { leftBottom.x + o.x, leftBottom.y + o.y };
            result.rightBottom = { rightBottom.x + o.x, rightBottom.y + o.y };
            return result;
        }

        Point operator*(const float scale) const {
            Point result;
            result.leftTop = { leftTop.x * scale, leftTop.y * scale };
            result.rightTop = { rightTop.x * scale, rightTop.y * scale };
            result.leftBottom = { leftBottom.x * scale, leftBottom.y * scale };
            result.rightBottom = { rightBottom.x * scale, rightBottom.y * scale };
            return result;
        }
    };


} // namespace Core
