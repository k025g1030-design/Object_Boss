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
	void Enemy::Input() {
	}
	void Enemy::Update() {

		
		if (hp_<=0)
		{
			return;
		}

		d_ = track_ - position_;

		float length = sqrtf(d_.x * d_.x + d_.y * d_.y);
		if (length != 0.0f) {
			d_.x /= length;
			d_.y /= length;
		}


		position_.x += d_.x * vel_.x;
		position_.y += d_.y * vel_.y;


		//position_.x += vel_.x;
		//position_.y += vel_.y;
		
	}
}