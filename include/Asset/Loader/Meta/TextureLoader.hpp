#pragma once
#include <string>
#include "Asset/Loader/Meta/IAssetLoader.hpp"
#include "Asset/MetaData/Texture.hpp"

/**

**/
namespace Asset {
    class TextureLoader : public IAssetLoader<Texture> {
    public:
        std::shared_ptr<Texture> LoadFromFile(const std::string& path, AssetManager& /*assets*/) override;
    };
}
