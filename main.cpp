#include <Windows.h>
#include "Game/GameApp.hpp"
#include "Core/Backend.hpp"
#include "Core/Config.hpp"
#include "Core/EngineAPI.hpp"



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ライブラリの初期化
    //Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);
    Engine::Initialize(
    "./Assets/Data/catalog.csv",
    "./Assets/Core/scene_all.json"
    );

    // キー入力結果を受け取る箱
    char keys[256] = {0};
    char preKeys[256] = {0};

    
	Game::GameApp gameApp;
	gameApp.Init();


    // ウィンドウの×ボタンが押されるまでループ
    while (Engine::Backend::ProcessStatus() == 0) {
        
        // キー入力を受け取る
        memcpy(preKeys, keys, 256);
        Engine::Backend::GetHitKeyStateAll(keys);

        //Novice::ScreenPrintf(0, 0, "%s", data["name"].get<std::string>().c_str());

		gameApp.Input();

		gameApp.Update();


        // フレームの開始
        Engine::Backend::StartFrame();
		
        gameApp.Render();

        // フレームの終了
        Engine::Backend::EndFrame();

        // ESCキーが押されたらループを抜ける
        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    // ライブラリの終了
    Engine::Backend::Finalize();
    return 0;
}


