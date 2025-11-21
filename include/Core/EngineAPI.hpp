#pragma once
#include <string>
#include "Engine/EngineCore.hpp"
#include "Core/Math.hpp"
#include "Engine/Asset/MetaData/Texture.hpp"
#include "Engine/Asset/MetaData/Sound.hpp"

#include "Engine/Asset/Data/AnimationData.hpp"
#include "Engine/Asset/Data/TileSetData.hpp"
#include "Engine/Asset/Data/Graphics/Sprite.hpp"
#include "Engine/Asset/Data/SoundData.hpp"
#include <memory>


/**

  「外部」エンジンのコア機能にアクセスするための API 群
  - ゲーム層が使う高階 API を定義
  - 内部で EngineCore インスタンスを保持し、そこから各種サブシステムにアクセスする
**/
namespace {
    Engine::EngineCore gEngine;
}

namespace Engine {
    
    //========================
    struct TextureHandle {
        std::string id;
    };

    struct SoundHandle {
        std::string id;
    };

    struct AnimHandle {
        std::string id;
    };

    struct TileSetHandle {
        std::string id;
    };



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

    void Initialize(const std::string& assetCatalogPath);


    // --- 描画用の高階 API ---
    void RenderSprite(const Core::Vector2 position, const Asset::Sprite& sprite);

    void RenderAnimetion(const Core::Vector2 position, const Asset::AnimationData& animData);
    // もしくは:
    // void DrawFrame(TextureHandle tex, const Frame& src, float x, float y);

    // --- サウンド再生 ---
    void PlaySound(const Asset::SoundData& soundData);
    void StopSound(const Asset::SoundData& soundData);
}
