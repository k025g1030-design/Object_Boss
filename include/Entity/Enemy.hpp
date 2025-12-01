#pragma once
#include "Core/Math.hpp"
#include "Entity/Player.hpp"

namespace Entity {
	class Enemy {
	public:
		explicit Enemy() {}
		~Enemy() {}
		void Draw();
		void Input();
		void Update(const Player& player);
		

		void SetPosition(const Core::Vector2& position) { position_ = position; }
		void SetVelocity(const Core::Vector2& velocity) { vel_ = velocity; }
		void SetSize(const Core::Vector2& size) { size_ = size; }
	
		void SetD(const Core::Vector2& d) { d_ = d; }
		

	private:

		Core::Vector2 d_;
		Core::Vector2 position_; 
		Core::Point point_;      
		Core::Vector2 vel_; 
		Core::Vector2 t_;
		Core::Vector2 size_;     
	};
}
