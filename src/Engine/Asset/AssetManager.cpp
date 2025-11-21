#include "Engine/Asset/AssetsManager.hpp"
#include "Engine/Asset/Loader/Meta/TextureLoader.hpp"
#include "Engine/Asset/Loader/Meta/SoundLoader.hpp"
#include "Engine/Asset/Loader/AnimationLoader.hpp"
#include "Engine/Asset/Loader/TileSetLoader.hpp"

namespace Asset {
    void AssetManager::Initialize(const std::string& catalogPath) {
        // ローダーの登録など初期化処理をここに書く
        catalog_.Load(catalogPath);
        RegisterLoader<Texture>("texture", std::make_shared<TextureLoader>());
        RegisterLoader<Sound>("sound", std::make_shared<SoundLoader>());
        RegisterLoader<AnimationData>("anim_meta", std::make_shared<AnimationLoader>());
        RegisterLoader<TileSetData>("tileset_meta", std::make_shared<TileSetLoader>());
    }

    void AssetManager::Unload(const std::string& id) {
        cache_.erase(id);
    }

    void AssetManager::UnloadAll() {
        cache_.clear();
    }
} // namespace Asset