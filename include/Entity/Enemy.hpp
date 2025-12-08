#pragma once
#include "Core/Math.hpp"
#include "Entity/Player.hpp"

namespace Entity {

	const int ENEMY_MAX_HP = 400;

	class Enemy {
	public:
		explicit Enemy() {}
		~Enemy() {}
		void Draw();
		void Input();
		void Update();
		

		void SetPosition(const Core::Vector2& position) { position_ = position; }
		void SetVelocity(const Core::Vector2& velocity) { vel_ = velocity; }
		void SetSize(const Core::Vector2& size) { size_ = size; }	
		void SetD(const Core::Vector2& d) { d_ = d; }
		void SetTrack(const Core::Vector2& track) { track_ = track; }
		void GetTrack(Core::Vector2& track) { track = track_; }	
		void SetHP(int hp) { hp_ = hp; }
		const int GetHP() { 
			if (hp_ < 0) {
				hp_ = 0;
			}
			return hp_; 
		}
		void SetDamage(int attack){ attack_ = attack; }


	private:

		Core::Vector2 d_;
		Core::Vector2 position_; 
		Core::Point point_;      
		Core::Vector2 vel_; 
		Core::Vector2 t_;
		Core::Vector2 size_;  
		
		Core::Vector2 track_;

		int hp_ = ENEMY_MAX_HP;
		
		int attack_ = 25;
	};
}
