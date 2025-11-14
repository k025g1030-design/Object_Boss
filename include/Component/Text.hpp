#pragma once
#include "Core/Math.hpp"
#include "Core/ResourceManager.hpp"
#include <string>
#include <Novice.h>


namespace Component {
    class TextSpan {
    public:
        explicit TextSpan(Core::Vector2 size, Core::Vector2 position, std::string name) : size_(size), position_(position), name_(name) {}
        explicit TextSpan(Core::Vector2 position, std::string name, Core::AnimeHandle cursorHandle) : size_(cursorHandle.size), position_(position), name_(name), cursorHandle_(cursorHandle) {}
        explicit TextSpan() {}

        void Render() const {
            if (!isVisible_) return;
            int x = static_cast<int>(position_.x);
            int y = static_cast<int>(position_.y);
            int w = static_cast<int>(size_.x);
            int h = static_cast<int>(size_.y);
            if (cursorHandle_.resource.textureHandle == -1) {
                Novice::DrawBox(x, y, w, h, 0, 0x404040FF, kFillModeSolid);
                Novice::DrawBox(x, y, w, h, 0, 0xFFFFFFFF, kFillModeWireFrame);
                Novice::ScreenPrintf(x + 10, y + h / 2 - 8, "%s", name_.c_str());
            } else {
                Novice::DrawBox(x, y, (int)cursorHandle_.size.x, (int)cursorHandle_.size.y, 0, 0x404040cc, kFillModeSolid);
                Novice::DrawSpriteRect(
                    x, y,
                    (int)cursorHandle_.posi.x, (int)cursorHandle_.posi.y,
                    (int)cursorHandle_.size.x, (int)cursorHandle_.size.y,
                    cursorHandle_.resource.textureHandle,
                    cursorHandle_.size.x / cursorHandle_.resource.size.x, 1, 0.0f, WHITE
                );
            }
        }
        void SetCursorHandle(Core::AnimeHandle handle) {
            cursorHandle_ = handle;
        }
        void SetName(std::string name) {
            name_ = name;
        }
        std::string GetName() {
            return name_;
        }
        void SetSize(Core::Vector2 size) {
            size_ = size;
        }
        Core::Vector2 GetSize() {
            return size_;
        }
        void SetPosition(Core::Vector2 position) {
            position_ = position;
        }
        bool IsVisible() const {
            return isVisible_;
        }
        void SetVisible(bool flag) {
            isVisible_ = flag;
        }

        void Open() {
            isVisible_ = true;
        }

        void Close() {
            isVisible_ = false;
        }

    private:
        Core::Vector2 size_;
        Core::Vector2 position_;
        bool isVisible_{ true };
        std::string name_;
        Core::AnimeHandle cursorHandle_;
    };
}

