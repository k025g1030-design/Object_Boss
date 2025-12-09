#pragma once
#include <string>

namespace Engine::Scene {
    class SceneChangeContext;
    class IScene {
    public:
        virtual ~IScene() = default;

        virtual void InitializeContext(const SceneChangeContext& ctx) = 0;

        // ライフサイクル 
        // ・スタックに追加されたときに呼び出される
        virtual void OnEnter() = 0;
        // ・スタックから取り除かれたときに呼び出される
        virtual void OnExit() = 0;

        // ・下の Scene がオーバーレイで覆われたとき(overlay)
        virtual void OnPause() = 0;
        // ・上の Scene が pop されたとき、下の Scene が前面に戻る(pop)
        virtual void OnResume() = 0;       

        // ・毎フレームの更新と描画
        virtual void Update() = 0;
        virtual void Render() = 0;

        void SetSceneId(const std::string& sceneId) { sceneId_ = sceneId; }
        const std::string& GetSceneId() const { return sceneId_; }
    private:
        // SceneManager に ID を付ける（例: "game.main"）
        std::string sceneId_;
    };

}