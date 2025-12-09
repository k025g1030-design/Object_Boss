#include "Game/GameApp.hpp"
#include "Core/Backend.hpp"


namespace Game {

	GameApp::GameApp() {
	}
	GameApp::~GameApp() {
	}
	void GameApp::Init() {
		// Initialization code here
		/*enemy_ = Entity::Enemy();
		enemy_.SetPosition({ 200.0f, 200.0f });
        enemy_.SetSize({ 50.0f, 50.0f });
		enemy_.SetVelocity({ 2.0f, 2.0f });
		enemy_.SetHP(Entity::ENEMY_MAX_HP);
		enemy_.SetD({});*/

		

	}

	void GameApp::Input() {
		// Input handling code here
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
	}
	void GameApp::Shutdown() {
		// Resource cleanup code here
	}

}
