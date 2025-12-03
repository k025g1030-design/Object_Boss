/*
https://sites.google.com/g.neec.ac.jp/kamata-engine/novice/reference/%E3%83%96%E3%83%AC%E3%83%B3%E3%83%89
*/
#pragma once
#include "Core/Math.hpp"
#include <string>
#include <Novice.h>


namespace Component {
    class Button {
    public:
        explicit Button(Core::Vector2 size, Core::Vector2 position, std::string name) : size_(size), position_(position), name_(name) {}
        explicit Button() {}

        bool Contains(Core::Vector2 p, Core::Vector2 sz, int mx, int my) {
            return mx >= p.x && mx <= p.x + sz.x && my >= p.y && my <= p.y + sz.y;
        }

        bool HandleMouse(int mx, int my, bool mouseDown, bool prevMouseDown) {
            if (!isEnabled_ || !isVisible_) {
                pressed = false; // 禁用或不可見時取消捕獲
                return false;
            }
            hovered = Contains(position_, size_, mx, my);

            // 按下開始（只在按下邊沿觸發）
            if (hovered && mouseDown && !prevMouseDown) {
                pressed = true; // 指針捕獲（開始在此按鈕上）
            }

            bool clicked = false;
            // 鬆開（只在鬆開邊沿判定）；若捕獲且在按鈕內→視為一次點擊
            if (pressed && !mouseDown && prevMouseDown) {
                if (hovered) {
                    isSelected_ = !isSelected_; // ← 只在這裡切換，一幀一次
                    clicked = true;
                }
                pressed = false; // 釋放捕獲
            }

            // 如果按著時滑出範圍就取消點擊：
            if (pressed && mouseDown && !hovered) {
                pressed = false;
            }

            return clicked;
        }

        Core::Vector2 GetSize() const {
            return size_;
        }
        Core::Vector2 GetPosition() const {
            return position_;
        }
        void SetPosition(Core::Vector2 pos) {
            position_ = pos;
        }
        void Open() {
            isEnabled_ = true;
            isVisible_ = true;
        }
        void Close() {
            isEnabled_ = false;
            isVisible_ = false;
        }

        bool IsEnabled() const {
            return isEnabled_;
        }
        void SetEnabled(bool flag) {
            isEnabled_ = flag;
        }
        bool IsVisible() const {
            return isVisible_;
        }
        void SetVisible(bool flag) {
            isVisible_ = flag;
        }

        bool IsSelected() const {
            return isSelected_;
        }

        void SetSelected(bool flag) {
            isSelected_ = flag;
        }

        void SetValue(int value) {
            value_ = value;
        }

        int GetValue() const {
            return value_;
        }

        void SetName(char* name) {
            name_ = name;
        }

        void SetName(char* name) {
            name_ = name;
        }

        void Render() const {
            if (!isVisible_) return;
            int x = static_cast<int>(position_.x);
            int y = static_cast<int>(position_.y);
            int w = static_cast<int>(size_.x);
            int h = static_cast<int>(size_.y);

            Novice::DrawBox(x, y, w, h, 0, 0x404040FF, kFillModeSolid);
            Novice::DrawBox(x, y, w, h, 0, 0xFFFFFFFF, kFillModeWireFrame);
            Novice::ScreenPrintf(x + 10, y + h / 2 - 8, "%s", name_.c_str());
            if (isSelected_) {
                Novice::DrawBox(x, y, w, h, 0, RED, kFillModeWireFrame);
            }
           

        }

    private:
        Core::Vector2 size_;
        Core::Vector2 position_;
        bool isEnabled_{ true };
        bool isVisible_{ true };
        bool isSelected_{ false };
        bool hovered{ false };
        bool pressed{ false };  // 是否在此按鈕上開始按下（捕獲）

        int value_{ -1 };
        std::string name_;
    };
}
