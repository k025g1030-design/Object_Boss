#pragma once
#include <string>
#include <memory>
#include <functional>
#include <unordered_map>
#include "Engine/Asset/Loader/Meta/IAssetLoader.hpp"
#include "Engine/Asset/AssetCatalog.hpp"
#include "Engine/Asset/ResourceHandle.hpp"

namespace Asset {
    class AssetManager {
    public:
        void Initialize(const std::string& catalogPath);

        template<typename T>
        T* Load(const std::string& assetId);

        template<typename T>
        T* Get(const std::string& id);    

        void Unload(const std::string& id);
        void UnloadAll();

        template<typename T>
        void RegisterLoader(const std::string& id, std::shared_ptr<IAssetLoader<T>> loader);

        // ハンドルを取得（内部で一度 Load<T> する）
        template<typename T>
        ResourceHandle<T> GetHandle(const std::string& assetId);

    private:
        // 
        using LoaderFunc = std::function<std::shared_ptr<void>(const std::string& path, AssetManager& assets)>;
        // 
        AssetCatalog catalog_;
        //
        std::unordered_map<std::string, std::shared_ptr<void>> cache_;
        //
        std::unordered_map<std::string, LoaderFunc> loaders_;

        template<typename T> friend class ResourceHandle; 
    };

    /*
    * 型消去と、元の T 型への再キャスト
    */
    template<typename T>
    void AssetManager::RegisterLoader(const std::string& type,
        std::shared_ptr<IAssetLoader<T>> loader) {
        if (loaders_.find(type) != loaders_.end()) {
            /*std::cerr << "[AssetManager] Loader for type '" << type
                << "' already registered.\n";*/
            return;
        }

        LoaderFunc fn = [loader](const std::string& path,
            AssetManager& assets)
            -> std::shared_ptr<void> {
            std::shared_ptr<T> res = loader->LoadFromFile(path, assets);
            return res; 
            };

        loaders_[type] = std::move(fn);
    }

    template<typename T>
    T* AssetManager::Load(const std::string& assetId) {
        // 1) cache 捜す
        auto it = cache_.find(assetId);
        if (it != cache_.end()) {
            return static_cast<T*>(it->second.get());
            // return std::static_pointer_cast<T>(it->second).get();
        }

        // 2) find catalog：id → {type, path}
        AssetInfo info = catalog_.Get(assetId);
        auto loaderIt = loaders_.find(info.type);
        if (loaderIt == loaders_.end()) {
            /*std::cerr << "[AssetManager] No loader for type: " << info.type << "\n";*/
            return nullptr;
        }

        LoaderFunc& fn = loaderIt->second;

        // 3) call loader：path → shared_ptr<void>
        std::shared_ptr<void> anyRes = fn(info.path, *this);

        // 4) save cache
        cache_[assetId] = anyRes;

        // 5)  T* を返す（元の T 型への再キャスト）
        return static_cast<T*>(anyRes.get());
    }

    template<typename T>
    T* AssetManager::Get(const std::string& assetId) {
        auto it = cache_.find(assetId);
        if (it != cache_.end()) {
            return static_cast<T*>(it->second.get());
        }
        return nullptr; // キャッシュに存在しない場合
    }

    template<typename T>
    ResourceHandle<T> AssetManager::GetHandle(const std::string& assetId) {
        Load<T>(assetId); // Load しておく
        return ResourceHandle<T>(this, assetId);
    }

    // ResourceHandle<T>::Get() を実装のはこちら
    template<typename T>
    T* ResourceHandle<T>::Get() const {
        if (!manager_) return nullptr;
        return manager_->Get<T>(assetId_);
    }
}