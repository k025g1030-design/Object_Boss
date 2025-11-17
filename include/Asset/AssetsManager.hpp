#pragma once
#include <string>
#include <memory>
#include "Asset/Loader/IAssetLoader.hpp"

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
        

    };
}