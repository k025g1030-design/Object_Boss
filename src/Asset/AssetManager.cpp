#include "Asset/AssetsManager.hpp"
#include "Asset/Loader/Meta/TextureLoader.hpp"
#include "Asset/Loader/Meta/SoundLoader.hpp"
#include "Asset/Loader/AnimationLoader.hpp"
#include "Asset/Loader/TileSetLoader.hpp"

namespace Asset {
    void AssetManager::Initialize() {
        // ローダーの登録など初期化処理をここに書く
        catalog_.Load("./Assets/catalog.csv");
        RegisterLoader<Texture>("texture", std::make_unique<TextureLoader>());
        RegisterLoader<Sound>("sound", std::make_unique<SoundLoader>());
        RegisterLoader<AnimationData>("anim_meta", std::make_unique<AnimationLoader>());
        RegisterLoader<TileSetData>("tileset_meta", std::make_unique<TileSetLoader>());

    }
    template<typename T>
    T* AssetManager::Load(const std::string& id) {
        // キャッシュに存在する場合はそれを返す
        auto it = cache_.find(id);
        if (it != cache_.end()) {
            return static_cast<T*>(it->second.get());
        }
        // カタログからアセット情報を取得
        AssetInfo assetInfo = catalog.Get(id);
        // ローダーを取得
        auto loaderIt = loaders.find(assetInfo.type);
        if (loaderIt == loaders.end()) {
            return nullptr; // ローダーが見つからない場合
        }
        // アセットをロード
        IAssetLoader<T>* loader = static_cast<IAssetLoader<T>*>(loaderIt->second.get());
        T* asset = loader->LoadFromFile(assetInfo.path);
        if (asset) {
            cache_[id] = std::shared_ptr<void>(asset);
        }
        return asset;
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

    template<typename T>
    void AssetManager::RegisterLoader(const std::string& id, std::unique_ptr<IAssetLoader<T>> loader) {
        // ローダー検査、重複登録防止
        if (loaders.find(type) != loaders.end()) {
            // std::cerr << "Loader for type '" << type << "' already registered\n";
            return;
        }

        LoaderFunc fn = [ldr = std::move(loader), this](const std::string& path)
            -> std::shared_ptr<void> {
            // 資源をローダーする：IAssetLoader<T> → shared_ptr<T>
            std::shared_ptr<T> res = ldr->LoadFromFile(path, *this);

            //  shared_ptr<void> に変換する、 cache に保存するため
            return res;
        };

        loaders[type] = std::move(fn);

    }
} // namespace Asset