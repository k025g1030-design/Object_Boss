#pragma once
#include "Engine/Framework/Scene/IScene.hpp"
#include <iostream>

namespace Scene {
    class MenuScene : public IScene {
    public:
        void OnEnter() override;
        void Update() override;
        void Render() override;
        void OnExit() override;

		
    private:
        // メニューシーン固有のメンバ変数をここに追加

        void HandleInput() {
            // 入力処理の実装
		}
        void UpdateAnimations() {
            // アニメーション更新の実装
            // ボタンのフェード&カーソル移動  
        }
        void DorwMenuBackground() {
            // メニュー背景の描画処理
		}
        void DrowMenuBottons() {
            // メニューボタンの描画処理
        }   
        void StopBGM() {
            // BGM停止処理
		}
        void ReleaseUI() {
           //Ui破棄
        }
        void GameLoop(IScene* currentSneme) {
            // ゲームループ処理
			currentSneme->OnEnter();
            while (true) {
                currentSneme->Update();
                currentSneme->Render();
				break; // 仮の終了条件
			}
			currentSneme->OnExit();
		}

    };
}