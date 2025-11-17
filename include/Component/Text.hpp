#pragma once
#include "Core/Math.hpp"
#include "Asset/ResourceHandle.hpp"
#include <string>
#include <Novice.h>


namespace Component {
    class TextSpan {
    public:
        explicit TextSpan(Core::Vector2 size, Core::Vector2 position, std::string name) : size_(size), position_(position), name_(name) {}
        explicit TextSpan() {}

        void Render() const {
            if (!isVisible_) return;
            int x = static_cast<int>(position_.x);
            int y = static_cast<int>(position_.y);
            int w = static_cast<int>(size_.x);
            int h = static_cast<int>(size_.y);

            Novice::DrawBox(x, y, w, h, 0, 0x404040FF, kFillModeSolid);
            Novice::DrawBox(x, y, w, h, 0, 0xFFFFFFFF, kFillModeWireFrame);
            Novice::ScreenPrintf(x + 10, y + h / 2 - 8, "%s", name_.c_str());
            
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
    };
}

