#include "Engine/System/GuiSystem.hpp"
#include "Core/EngineAPI.hpp"

namespace Engine::System {
    void GuiSystem::Initialize(Engine::System::GameSession* session) {
        session_ = session;
    }

    void GuiSystem::Update(float dt) {
        dt;

    }

    void GuiSystem::Render() {
        float ShowMaxPlayerHP = (float)(Entity::PLAYER_MAX_HP * 2);
        float ShowPlayerHP = (float)(session_->player.GetHP() * 2);

        Engine::RenderBox(
            {17.f, (float)(Core::kWindowHeight - 50)},
            { ShowMaxPlayerHP , 30.f},
            0x000000FF,
            1
        );
        Engine::RenderBox(
            { 17.f, (float)(Core::kWindowHeight - 50)},
            { ShowPlayerHP, 30.f },
            0x00FF00FF,
            0
        );

        if (session_->enemy.GetHP() > 0) {
            float ShowMaxBossHP = (float)(Entity::ENEMY_MAX_HP * 2);
            float ShowBossHP = (float)(session_->enemy.GetHP() * 2);
            Engine::RenderBox(
                { 17.f, 20.f },
                { ShowMaxBossHP, 30.f },
                0x000000FF,
                1
            );
            Engine::RenderBox(
                { 17.f, 20.f },
                { ShowBossHP, 30.f },
                0xFF0000FF,
                0
            );
        }

    }
    
}
