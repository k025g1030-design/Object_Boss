#pragma once
#include"Core/Math.hpp"

namespace Entity {
	class Boss {
	public:
		explicit Boss() = default;
		~Boss() = default;
		void Update();
		void Render();



	private:
		Core::Vector2 position_;
		Core::Vector2 velocity_;

	

	};
}



