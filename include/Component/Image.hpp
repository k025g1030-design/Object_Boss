#pragma once
#include "Core/Math.hpp"
#include <Novice.h>


namespace Component {
    class ImageSpan {
    public:
        explicit ImageSpan(Core::Vector2 size, Core::Vector2 position) : size_(size), position_(position){}
        explicit ImageSpan() {}

        void Render() const {
            if (!isVisible_) return;
            int x = static_cast<int>(position_.x);
            int y = static_cast<int>(position_.y);
            int w = static_cast<int>(size_.x);
            int h = static_cast<int>(size_.y);

            Novice::DrawBox(x, y, w, h, 0, 0x404040FF, kFillModeSolid);
            Novice::DrawBox(x, y, w, h, 0, 0xFFFFFFFF, kFillModeWireFrame);
            
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
    };
}

