#include "Entity/Player.hpp"
#include "Core/Backend.hpp"



namespace Entity {
	void Player::Draw(Engine::System::Camera camera) {
		Engine::Backend::DrawBox(static_cast<int>(position_.x - camera.x), static_cast<int>(position_.y - camera.y),
			static_cast<int>(size_.x), static_cast<int>(size_.y),
			0.0f, RED, kFillModeSolid);
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