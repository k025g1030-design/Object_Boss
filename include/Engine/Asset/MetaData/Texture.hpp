#pragma once
#include <string>
#include "Core/Config.hpp"

/**

**/
namespace Asset {
    struct Frame {
        int x, y, w, h;
    };

    struct GridVector {
        int row;
        int col;
    };

    struct Grid{
        int cellW = Core::PIXELS_PER_UNIT;
        int cellH = Core::PIXELS_PER_UNIT;
        int marginX;
        int marginY;
        int spacingX;
        int spacingY;
        GridVector count;
    };

    struct Scale {
        int pixelsPerUnit = Core::PIXELS_PER_UNIT;
    };

    class Texture {
    public:
        explicit Texture() = default;
        explicit Texture(int handle, int width, int height, std::string path) : handle_(handle), width_(width), height_(height), path_(path) {}
        ~Texture() = default;

        int GetHandle() const {
            return handle_;
        }
        void SetHandle(int handle) {
            handle_ = handle;
        }
        int GetWidth() const {
            return width_;
        }
        void SetWidth(int width) {
            width_ = width;
        }
        int GetHeight() const {
            return height_;
        }
        void SetHeight(int height) {
            height_ = height;
        }
        std::string GetPath() const {
            return path_;
        }
        void SetPath(const std::string& path) {
            path_ = path;
        }

    private:
        int handle_{ -1 };

        int width_{ 0 };
        int height_{ 0 };

        std::string path_{ "" };
    };

}
