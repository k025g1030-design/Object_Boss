#include "Game/GameApp.hpp"

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
		enemy_.SetD({});
	
		//enemy_.SetT({});

		player_ = Entity::Player();
		player_.SetPosition({ 400.0f, 300.0f });
		player_.SetSize({ 50.0f, 50.0f });
		player_.SetVelocity({ 0.0f, 0.0f });
	}
	void GameApp::Input() {
		// Input handling code here
		player_.Input();
	} 
	void GameApp::Update() {
		// ゲームロジック更新コードここに
		
		enemy_.SetTrack(player_.GetPosition());
		player_.Update();
		enemy_.Update();

        

	} 

	void GameApp::Render() {
		// 描画

        Engine::GetCore().GetSceneManager().Render();

	
		/*player_.Draw();

		enemy_.Draw();*/
	}
	void GameApp::Shutdown() {
		// Resource cleanup code here
	}

}
