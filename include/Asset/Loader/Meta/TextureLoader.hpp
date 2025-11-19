#pragma once
#include <string>
#include "Asset/Loader/Meta/IAssetLoader.hpp"
#include "Asset/MetaData/Texture.hpp"

/**

**/
namespace Asset {
    class TextureLoader : public IAssetLoader<Texture> {
    public:
        Texture* LoadFromFile(const std::string& path) override {
            
        }
    };
}
