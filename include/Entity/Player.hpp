#pragma once
#include "Core/Math.hpp" 
#include "Engine/System/Camera.hpp"
#include <vector>

namespace Entity {
	const int PLAYER_MAX_HP = 100;

	class Player {
	public:
		explicit Player() {
			
		}
		~Player() {}

		// 描画
		// void Draw(Engine::System::Camera camera);


		// 更新
		void Update();

		const Core::Vector2& GetPosition() const { return position_; }
		void SetPosition(const Core::Vector2& position) { position_ = position; }
		void SetVelocity(const Core::Vector2& velocity) { vel_ = velocity; }
		void SetSize(const Core::Vector2& size) { size_ = size; }
		void SetDic(std::string dic) {
			dic_ = dic;
		}
		const std::string GetDic() const {
			return dic_;
		}
		void SetPrePos(Core::VectorInt2 prePos) {
			prePos_ = prePos;
		}
		const Core::VectorInt2 GetPrePos() {
			return prePos_;
		}
		void PopSkill() {
			if (skillPool_.size() < 3) {
				skillPool_.push_back({ (int)position_.x, (int)position_.y });
			}
		}
		std::vector<Core::VectorInt2>& GetSkillPool() {
			return skillPool_;
		}
	
		void SetHP(int hp) { hp_ = hp; }
		const int GetHP() { 
			if (hp_ <= 0)
			{
				hp_ = 0;
			}
			if (hp_ >=PLAYER_MAX_HP)
			{
				hp_ = PLAYER_MAX_HP;
			}
			return hp_; 
		}
		

	private:
		Core::Vector2 position_; // 位置情報
		Core::Point point_;      // 頂点情報
		Core::Vector2 vel_;      // 速度
		Core::Vector2 size_;     // 大きさ
		int hp_ = PLAYER_MAX_HP;

		std::string dic_ = "down";
		Core::VectorInt2 prePos_ = { -9999, -9999 };
		std::vector<Core::VectorInt2> skillPool_;
	

	};

}