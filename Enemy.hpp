#pragma once
#include "struct.hpp"

namespace Entity {
	class Enemy {
	public:
        Vecter2 pos_;
		Vecter2 leftTopPos_;
		Vecter2 rightTopPos_;
		Vecter2 leftBottomPos_;
		Vecter2 rightBottomPos_;
		float speed_;
		Vecter2 vel_;
		Vecter2 move_;
		Vecter2 NeoMove_;
		float width_;
		float height_;
	public:

		Enemy();
		~Enemy();
		void Draw() {

		}
		void Input() {

		}
		void Update() {

		}
	};
}
