#pragma once
#include "Core/Math.hpp"
#include "Asset/ResourceHandle.hpp"
#include <Novice.h>


namespace Component {
    class ImageSpan {
    public:
        explicit ImageSpan(Core::Vector2 size, Core::Vector2 position) : size_(size), position_(position){}
        explicit ImageSpan(Core::Vector2 position, Core::AnimeHandle cursorHandle) : size_(cursorHandle.size), position_(position), cursorHandle_(cursorHandle) {}
        explicit ImageSpan() {}

        void Render() const {
            if (!isVisible_) return;
            int x = static_cast<int>(position_.x);
            int y = static_cast<int>(position_.y);
            int w = static_cast<int>(size_.x);
            int h = static_cast<int>(size_.y);
            if (cursorHandle_.resource.textureHandle == -1) {
                Novice::DrawBox(x, y, w, h, 0, 0x404040FF, kFillModeSolid);
                Novice::DrawBox(x, y, w, h, 0, 0xFFFFFFFF, kFillModeWireFrame);
            } else {
                Novice::DrawSpriteRect(
                    x, y,
                    (int)cursorHandle_.posi.x, (int)cursorHandle_.posi.y,
                    (int)cursorHandle_.size.x, (int)cursorHandle_.size.y,
                    cursorHandle_.resource.textureHandle,
                    (cursorHandle_.size.x / cursorHandle_.resource.size.x * cursorHandle_.resource.scale), 
                    (cursorHandle_.size.y / cursorHandle_.resource.size.y * cursorHandle_.resource.scale), 
                    0.0f, WHITE
                );
            }
        }
        void SetCursorHandle(Core::AnimeHandle handle) {
            cursorHandle_ = handle;
        }
        void SetSize(Core::Vector2 size) {
            size_ = size;
        }
        Core::Vector2 GetSize() const {
            return size_;
        }

        void Open() {
            isVisible_ = true;
        }

        void Close() {
            isVisible_ = false;
        }

        void SetPosition(Core::Vector2 position) {
            position_ = position;
        }
        Core::Vector2 GetPosition() const {
            return position_;
        }
        bool IsVisible() const {
            return isVisible_;
        }
        void SetVisible(bool flag) {
            isVisible_ = flag;
        }

    private:
        Core::Vector2 size_;
        Core::Vector2 position_;
        bool isVisible_{ true };
        Core::AnimeHandle cursorHandle_;
    };
}

