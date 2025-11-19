#include <Windows.h>
#include <nlohmann/json.hpp>
#include <fstream> 
#include "Game/GameApp.hpp"
#include "Core/Backend.hpp"

const char* kWindowTitle = "Object_Boss";

using json = nlohmann::json;

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ライブラリの初期化
    //Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);
    Engine::Backend::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

    // キー入力結果を受け取る箱
    char keys[256] = {0};
    char preKeys[256] = {0};

    /*std::ifstream f("./Assets/Data/example.json");
    json data = json::parse(f);*/
    
	Game::GameApp gameApp;
	gameApp.Init();


    // ウィンドウの×ボタンが押されるまでループ
    while (Engine::Backend::ProcessStatus() == 0) {
        // フレームの開始
        Engine::Backend::StartFrame();

        
        // キー入力を受け取る
        memcpy(preKeys, keys, 256);
        Engine::Backend::GetHitKeyStateAll(keys);

        //Novice::ScreenPrintf(0, 0, "%s", data["name"].get<std::string>().c_str());

		gameApp.Input();

		gameApp.Update();
		
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


