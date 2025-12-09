#include "Game/GameApp.hpp"
#include "Core/Backend.hpp"


namespace Game {

	GameApp::GameApp() {
	}
	GameApp::~GameApp() {
	}
	void GameApp::Init() {
		// Initialization code here
		enemy_ = Entity::Enemy();
		enemy_.SetPosition({ 200.0f, 200.0f });
        enemy_.SetSize({ 50.0f, 50.0f });
		enemy_.SetVelocity({ 2.0f, 2.0f });
		enemy_.SetHP(Entity::ENEMY_MAX_HP);
		enemy_.SetD({});

		

	}

	void GameApp::Input() {
		// Input handling code here
		/*player_.Input();
		if (Novice::CheckHitKey(DIK_E))
		{
			player_.SetHP(player_.GetHP()-1);
		}

		if (Novice::CheckHitKey(DIK_Q))
		{
			player_.SetHP(player_.GetHP() + 1);
		}

		if (Novice::CheckHitKey(DIK_C)) {
			enemy_.SetHP(enemy_.GetHP() - 1);
		}*/
        Engine::GetCore().GetInputSystem().Poll();
	} 

	void GameApp::Update() {
        Engine::GetCore().GetInputSystem().Update(5.f);
		// ゲームロジック更新コードここに
		Engine::GetCore().GetSceneManager().Update(1.0f / 60.0f);

		
		/*enemy_.SetTrack(player_.GetPosition());
		player_.Update();
		enemy_.Update();*/

	} 

	void GameApp::Render() {
		// 描画

        Engine::GetCore().GetSceneManager().Render();
		
		/*player_.Draw();

		enemy_.Draw();

		Engine::Backend::DrawBox(10, 40, Entity::PLAYER_MAX_HP*2, 20, 0, BLACK, kFillModeWireFrame);
		Engine::Backend::DrawBox(10, 40, player_.GetHP()*2, 20, 0, BLUE, kFillModeSolid);
		Engine::Backend::DrawBox(10,10, Entity::ENEMY_MAX_HP*2,20,0,BLACK, kFillModeWireFrame);
		Engine::Backend::DrawBox(10,10, enemy_.GetHP()*2, 20, 0, RED, kFillModeSolid);*/


	}
	void GameApp::Shutdown() {
		// Resource cleanup code here
	}

}
