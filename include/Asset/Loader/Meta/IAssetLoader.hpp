#pragma once

/**

**/
namespace Asset {
    template<typename T>
    class IAssetLoader {
    public:
        virtual ~IAssetLoader() = default;
        virtual T* LoadFromFile(const std::string& path) = 0;
    };
}