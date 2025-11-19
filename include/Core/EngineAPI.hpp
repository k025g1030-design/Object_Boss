// EngineAPI.h
#pragma once
#include <string>
#include "Core/Math.hpp"
#include "Asset/MetaData/Texture.hpp"
#include "Asset/MetaData/Sound.hpp"

#include "Asset/Data/AnimationData.hpp"
#include "Asset/Data/TileSetData.hpp"
#include "Asset/Graphics/Sprite.hpp"
#include "Asset/Data/SoundData.hpp"
#include <memory>

namespace Engine {


    // --- 描画用の高階 API ---
    void RenderSprite(const Core::Vector2 position, const Asset::Sprite& sprite);

    void RenderAnimetion(const Core::Vector2 position, const Asset::AnimationData& animData);
    // もしくは:
    // void DrawFrame(TextureHandle tex, const Frame& src, float x, float y);

    // --- サウンド再生 ---
    void PlaySound(const Asset::SoundData& soundData);
    void StopSound(const Asset::SoundData& soundData);
}
