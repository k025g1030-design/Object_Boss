#include "Core/EngineAPI.hpp"
#include "Core/Backend.hpp"
#include "Core/Config.hpp"

namespace Engine {
    void Initialize(const std::string& assetCatalogPath) {
        Engine::Backend::Initialize(Core::kWindowTitle, Core::kWindowWidth, Core::kWindowHeight);
        gEngine.Init(assetCatalogPath);
    }

    void RenderSprite(const Core::Vector2 position, const Asset::Sprite& sprite) {
        position;
        sprite;
    }

    void RenderAnimetion(const Core::Vector2 position, const Asset::AnimationData& animation) {
        position;
        animation;
    }

    void PlaySound(const Asset::SoundData& soundData) {
        soundData;
    }

    void StopSound(const Asset::SoundData& soundData) {
        soundData;
    }
}
