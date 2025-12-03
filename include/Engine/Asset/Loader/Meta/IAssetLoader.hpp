#pragma once
#include <string>
#include <memory>

/**

**/
namespace Engine::Asset {
    class AssetManager; 

    template<typename T>
    class IAssetLoader {
    public:
        virtual ~IAssetLoader() = default;
        virtual std::shared_ptr<T> LoadFromFile(const std::string& path, AssetManager& assets) = 0;
    };
}