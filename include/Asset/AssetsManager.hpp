#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include "Asset/Loader/IAssetLoader.hpp"
#include "Asset/AssetCatalog.hpp"

namespace Asset {
    class AssetManager {
    public:
        template<typename T>
        T* Load(const std::string& id);   

        template<typename T>
        T* Get(const std::string& id);    

        void Unload(const std::string& id);
        void UnloadAll();

        template<typename T>
        void RegisterLoader(std::unique_ptr<IAssetLoader<T>> loader);

    private:
        //
        AssetCatalog catalog;
        //
        std::unordered_map<std::string, std::shared_ptr<void>> cache;
        //
        std::unordered_map<std::string, std::unique_ptr<IAssetLoader<void>>> loaders;
    };
}