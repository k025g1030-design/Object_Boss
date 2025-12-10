#pragma once
#include <string>
#include "Engine/EngineCore.hpp"
#include "Core/Math.hpp"
#include "Engine/Asset/MetaData/Texture.hpp"
#include "Engine/Asset/MetaData/Sound.hpp"

#include "Engine/Asset/Data/AnimationData.hpp"
#include "Engine/Asset/Data/TileSetData.hpp"
#include "Engine/Asset/Data/Sprite.hpp"
#include "Engine/Asset/Data/SoundData.hpp"
#include <Engine/Asset/Data/LevelData.hpp>
#include "Engine/Asset/Data/MapData.hpp"


#include <memory>


/**

  「外部」エンジンのコア機能にアクセスするための API 群
  - ゲーム層が使う高階 API を定義
  - 内部で EngineCore インスタンスを保持し、そこから各種サブシステムにアクセスする
**/


namespace Engine {

    
    //========================
    struct TextureHandle {
        std::string id;
    };

    struct SoundHandle {
        std::string id;
    };

    struct TextStoryHandle {
        std::string id;
    };

    struct TileSetHandle {
        std::string id;
    };

    struct AnimHandle {
        std::string id;
    };




    //========================
    // Game層が使う API
    //========================

    // --- 資源取得（Catalog 上の ID を指定） ---
    TextureHandle GetTextureHandle(const std::string& assetId);   // 例: "tex.bg.ui"
    SoundHandle GetSoundHandle(const std::string& assetId);   // 例: "sou.bgm"


    TextStoryHandle GetTextStoryHandle(const std::string& assetId);   // 例: "data.tex.story"
    TileSetHandle GetTileSetHandle(const std::string& assetId); //  例: "data.tileset.map", "data.tileset.ui", "data.tileset.item"
    AnimHandle GetAnimHandle(const std::string& assetId); //  例: "data.sheet.player"

    // --- 高階データへのアクセス（const ポインタで閲覧のみ） ---
    const Asset::AnimationData* GetAnimationData(AnimHandle handle);
    const Asset::TileSetData* GetTileSetData(TileSetHandle handle);
    const Asset::Sprite* GetSprite(TextureHandle handle);

    Engine::EngineCore& GetCore();

    bool MouseLeftClicked();

    void GetMousePosition(int* x, int* y);

    void RenderText(const Core::Vector2 position, const std::string& text);



    // --- エンジン初期化 ---
    void Initialize(const std::string& assetCatalogPath, const std::string& scenesCatalogPath);


    // --- 描画用の高階 API ---
    void RenderSprite(const Core::Vector2 position, const Asset::Sprite& sprite);

    void RenderFullScreenQuad(unsigned int color);
    void RenderLine(const Core::VectorInt2 start, const Core::VectorInt2 end);

    void RenderBox(const Core::Vector2 position, const Core::Vector2 size, unsigned int color, int fillMode);           

    void RenderAnimation(const Core::Vector2 position, Engine::Asset::Frame frame, const Asset::Texture* texture);

    void RenderTile(const Core::Vector2 position, const Asset::TileSetData* tileSetData, const std::string& tileId);

    void RenderAnimetion(const Core::Vector2 position, const Asset::AnimationData& animData);


    // --- サウンド再生 ---
    void PlaySound(const Asset::SoundData& soundData);
    void StopSound(const Asset::SoundData& soundData);
}
