#include "Engine/Asset/AssetsManager.hpp"
#include "Engine/Asset/Loader/Meta/TextureLoader.hpp"
#include "Engine/Asset/Loader/Meta/SoundLoader.hpp"
#include "Engine/Asset/Loader/AnimationLoader.hpp"
#include "Engine/Asset/Loader/TileSetLoader.hpp"
#include "Engine/Asset/Loader/SpriteLoader.hpp"
#include "Engine/Asset/Loader/MapDataLoader.hpp"

namespace Engine::Asset {
    void AssetManager::Initialize(const std::string& catalogPath) {
        // ローダーの登録など初期化処理をここに書く
        catalog_.Load(catalogPath);
        RegisterLoader<Texture>(AssetType::Texture, std::make_shared<TextureLoader>());
        RegisterLoader<Sound>(AssetType::Sound, std::make_shared<SoundLoader>());
        RegisterLoader<AnimationData>(AssetType::AnimClipData, std::make_shared<AnimationLoader>());
        RegisterLoader<TileSetData>(AssetType::TileSetData, std::make_shared<TileSetLoader>());
        RegisterLoader<Sprite>(AssetType::SpriteSheet, std::make_shared<SpriteLoader>());
        RegisterLoader<MapData>(AssetType::MapSourceData, std::make_shared<MapDataLoader>());



    }

    void AssetManager::Unload(const std::string& assetId) {
        cache_.erase(assetId);
    }

    void AssetManager::UnloadAll() {
        cache_.clear();
    }
} // namespace Asset