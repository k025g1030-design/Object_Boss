#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include "Asset/Loader/Meta/IAssetLoader.hpp"
#include "Asset/AssetCatalog.hpp"

namespace Asset {
    class AssetManager {
    public:
        void Initialize();

        template<typename T>
        T* Load(const std::string& id);   

        template<typename T>
        T* Get(const std::string& id);    

        void Unload(const std::string& id);
        void UnloadAll();

        template<typename T>
        void RegisterLoader(const std::string& id, std::unique_ptr<IAssetLoader<T>> loader);

    private:
        //
        AssetCatalog catalog_;
        //
        std::unordered_map<std::string, std::shared_ptr<void>> cache_;
        //
        std::unordered_map<std::string, std::unique_ptr<IAssetLoader<void>>> loaders_;
    };
}