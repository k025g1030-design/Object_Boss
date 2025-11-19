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

    struct ResourceTables {
        std::unordered_map<Engine::TextureHandle, std::shared_ptr<Asset::Texture>> textures;
        std::unordered_map<Engine::SoundHandle, std::shared_ptr<Asset::Sound>>   sounds;
        std::unordered_map<Engine::AnimHandle, Asset::AnimationData>    animations;
        std::unordered_map<Engine::TileSetHandle, Asset::TileSetData>      tilesets;

        Engine::TextureHandle nextTexId = 1;
        Engine::SoundHandle   nextSndId = 1;
        Engine::AnimHandle    nextAnimId = 1;
        Engine::TileSetHandle nextTileId = 1;
    };

    extern ResourceTables gResources;

    using TextureHandle = std::uint32_t;  // Texture のID（実体はエンジン内部）
    using SoundHandle = std::uint32_t;  // Sound のID
    using AnimHandle = std::uint32_t;  // AnimationData のID
    using TileSetHandle = std::uint32_t;  // TileSetData のID

    

    //========================
    // Game層が使う API
    //========================

    // --- 資源取得（Catalog 上の ID を指定） ---
    TextureHandle  GetTextureHandle(const std::string& assetId);   // 例: "tex.player"
    SoundHandle    GetSoundHandle(const std::string& assetId);   // 例: "se.jump"
    AnimHandle     GetAnimHandle(const std::string& assetId);   // 例: "anim.player"
    TileSetHandle  GetTileSetHandle(const std::string& assetId);   // 例: "tileset.stage1"

    // --- 高階データへのアクセス（const ポインタで閲覧のみ） ---
    const Asset::AnimationData* GetAnimationData(AnimHandle handle);
    const Asset::TileSetData* GetTileSetData(TileSetHandle handle);

    // --- 描画用の高階 API ---
    void RenderSprite(const Core::Vector2 position, const Asset::Sprite& sprite);

    void RenderAnimetion(const Core::Vector2 position, const Asset::AnimationData& animData);
    // もしくは:
    // void DrawFrame(TextureHandle tex, const Frame& src, float x, float y);

    // --- サウンド再生 ---
    void PlaySound(const Asset::SoundData& soundData);
    void StopSound(const Asset::SoundData& soundData);
}
