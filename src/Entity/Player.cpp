#include <Novice.h>
#include "Entity/Player.hpp"

namespace Entity {
	void Player::Draw() {
		Novice::DrawBox(static_cast<int>(position_.x), static_cast<int>(position_.y),
			static_cast<int>(size_.x), static_cast<int>(size_.y),
			0.0f, RED, kFillModeSolid);
	}
	void Player::Input() {
		if (Novice::CheckHitKey(DIK_UP)||Novice::CheckHitKey(DIK_W)) {
			vel_.y -= 5.0f;
		}
		if (Novice::CheckHitKey(DIK_DOWN) || Novice::CheckHitKey(DIK_S)) {
			vel_.y += 5.0f;
		}
		if (Novice::CheckHitKey(DIK_LEFT) || Novice::CheckHitKey(DIK_A)) {
			vel_.x -= 5.0f;
		}
		if (Novice::CheckHitKey(DIK_RIGHT) || Novice::CheckHitKey(DIK_D)) {
			vel_.x += 5.0f;
		}
	}
	void Player::Update() {
		
		if (hp_ <= 0)
		{
			return;
		}
		position_.x += vel_.x;
		position_.y += vel_.y;
		vel_.x = 0.0f;
		vel_.y = 0.0f;
	}
}