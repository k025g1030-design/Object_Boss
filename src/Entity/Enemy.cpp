#include "Entity/Enemy.hpp"
#include "Entity/Player.hpp"
#include "Core/Math.hpp"
#include <Novice.h>
#include <cmath>

namespace Entity {

	void Enemy::Draw() {
		Novice::DrawBox(static_cast<int>(position_.x), static_cast<int>(position_.y),
			static_cast<int>(size_.x), static_cast<int>(size_.y),
			0.0f, WHITE, kFillModeSolid);
	}

	
	
	void Enemy::Update() {

		if (hp_<=0)
		{
			return;
		}

		Core::Vector2 d = track_ - position_;

		float length = sqrtf(d.x * d.x + d.y * d.y);
		if (length != 0.0f) {
			d.x /= length;
			d.y /= length;
		}

		position_.x += d.x * 3;
		position_.y += d.y * 3;

		//position_.x += vel_.x;
		//position_.y += vel_.y;
		
	}
}