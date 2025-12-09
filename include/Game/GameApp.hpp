#pragma once
#include "Entity/Player.hpp"
#include "Entity/Enemy.hpp"
#include "Core/EngineAPI.hpp"

#include "Engine/System/InputSystem.hpp"
#include "Engine/System/ActorSystem.hpp"
#include "Engine/System/GuiSystem.hpp"
#include "Engine/System/MapSystem.hpp"

namespace Game {
	struct GameSession {
		
    };

	class GameApp {
	public:
		GameApp();
		~GameApp();

		/*初期化 */
		void Init();

		/* 入力処理 */
		void Input();

		/* 更新処理　GameLogic */
		void Update();

		/* 描画処理 */
		void Render();

		/* リソース消し */
		void Shutdown();

	private:
		// Private members and methods
		Entity::Player player_;
		Entity::Enemy enemy_;



	};

}