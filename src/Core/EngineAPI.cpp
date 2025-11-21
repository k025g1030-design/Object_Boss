#include "Core/EngineAPI.hpp"

namespace Engine {
    void Initialize(const std::string& assetCatalogPath) {
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
