#include "Entity/Enemy.hpp"
#include <Novice.h>

namespace Entity {
	void Enemy::Draw() {
		Novice::DrawBox(static_cast<int>(position_.x), static_cast<int>(position_.y),
			static_cast<int>(size_.x), static_cast<int>(size_.y),
			0.0f, WHITE, kFillModeSolid);
	}
	void Enemy::Input() {
	}
	void Enemy::Update() { 
		position_.x += vel_.x;
		//position_.y += 1;
	}
}