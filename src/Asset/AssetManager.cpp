#include "Asset/AssetsManager.hpp"
#include "Asset/Loader/Meta/TextureLoader.hpp"
#include "Asset/Loader/Meta/SoundLoader.hpp"
#include "Asset/Loader/AnimationLoader.hpp"
#include "Asset/Loader/TileSetLoader.hpp"

namespace Asset {
    void AssetManager::Initialize(const std::string& catalogPath) {
        // ローダーの登録など初期化処理をここに書く
        catalog_.Load(catalogPath);
        RegisterLoader<Texture>("texture", std::make_shared<TextureLoader>());
        RegisterLoader<Sound>("sound", std::make_shared<SoundLoader>());
        RegisterLoader<AnimationData>("anim_meta", std::make_shared<AnimationLoader>());
        RegisterLoader<TileSetData>("tileset_meta", std::make_shared<TileSetLoader>());

    }
  

    template<typename T>
    T* AssetManager::Get(const std::string& id) {
        auto it = cache_.find(id);
        if (it != cache_.end()) {
            return static_cast<T*>(it->second.get());
        }
        return nullptr; // キャッシュに存在しない場合
    }

    void AssetManager::Unload(const std::string& id) {
        cache_.erase(id);
    }

    void AssetManager::UnloadAll() {
        cache_.clear();
    }
} // namespace Asset