#include "Engine/System/ActorSystem.hpp"
#include "Core/EngineAPI.hpp"

namespace Engine::System {

    void ActorSystem::Initialize(Engine::System::GameSession* session) {
        // 初期化処理があればここに記述
        session_ = session;

        playerAnime_ = Engine::GetCore().GetAssetManager().Load<Engine::Asset::AnimationData>("data.sheet.player");

        bossAnime_ = Engine::GetCore().GetAssetManager().Load<Engine::Asset::AnimationData>("data.sheet.boss");
    }

    void ActorSystem::MovePlayer(Core::Vector2 delta) {

        Core::Vector2 newPos = session_->player.GetPosition() + delta;
        int tx = static_cast<int>(newPos.x / Core::PIXELS_PER_UNIT);
        int ty = static_cast<int>(newPos.y / Core::PIXELS_PER_UNIT);

        if (!Engine::GetCore().GetMapSystem().GetCurrentMap()->IsSolid(tx, ty)) {
            session_->player.SetPosition(newPos);
        }
    }

    std::string GetInputDic() {
        std::string key = "";
        Core::Vector2 inputSnapshot = Engine::GetCore().GetInputSystem().GetInputSnapshot();
        if (inputSnapshot.y > 0) {
            key = "down";
        } else if (inputSnapshot.y < 0 ){
            key = "up";
        }
        if (inputSnapshot.x > 0) {
            key = "right";
        } else if (inputSnapshot.x < 0) {
            key = "left";
        }
        

        return key;
    }
    void ActorSystem::PlayAnime(float dt) {
        std::string dic = GetInputDic();
        if (session_->player.GetDic() != dic && !dic.empty()) {
            session_->player.SetDic(dic);
        }
        Engine::Asset::AnimationClip clip = playerAnime_->clips.at(session_->player.GetDic());
        animTime_ += dt;

        // 每張圖的時間
        float frameDuration = 1.0f / clip.fps;

        // 目前經過了幾張
        int frameCount = static_cast<int>(clip.frameIndices.size());
        int totalFrames = static_cast<int>(animTime_ / frameDuration);

        // 迴圈播放
        currentIndex_ = totalFrames % frameCount;
    }

    void ActorSystem::MoveEnemy() {
        session_->enemy.SetTrack(session_->player.GetPosition());
        session_->enemy.Update();
    }

    void ActorSystem::Update(float dt) { 
        
        this->PlayAnime(dt);

        this->MoveEnemy();

        Core::Vector2 velocity = Engine::GetCore().GetInputSystem().GetVelocity();
        this->MovePlayer(velocity);
    }

    void ActorSystem::Render(Camera camera) {
        //session_->player.Draw(camera);
        if (session_->player.GetHP() > 0) {
            Engine::Asset::AnimationClip clip = playerAnime_->clips.at(session_->player.GetDic());
            int frameIdx = clip.frameIndices[currentIndex_];
            const Engine::Asset::Frame& f = playerAnime_->frames[frameIdx];
            Core::Vector2 screenPos = {
                static_cast<float>(session_->player.GetPosition().x - (f.w / 2) - camera.x),
                static_cast<float>(session_->player.GetPosition().y - (f.h / 2) - camera.y)
            };
            Engine::RenderAnimation(screenPos, f, playerAnime_->texture);
        }

        if (session_->enemy.GetHP() > 0) {
            Engine::Asset::AnimationClip clip = bossAnime_->clips.at("down");
            int frameIdx = clip.frameIndices[currentIndex_];
            const Engine::Asset::Frame& f = bossAnime_->frames[frameIdx];
            Core::Vector2 screenPos = {
                static_cast<float>(session_->enemy.GetPosition().x - (f.w / 2) - camera.x),
                static_cast<float>(session_->enemy.GetPosition().y - (f.h / 2) - camera.y)
            };
            
            Engine::RenderAnimation(screenPos, f, bossAnime_->texture);
        }
    }

}
