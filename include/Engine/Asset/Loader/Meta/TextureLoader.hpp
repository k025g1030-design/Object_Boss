#pragma once
#include <string>
#include "Engine/Asset/Loader/Meta/IAssetLoader.hpp"
#include "Engine/Asset/MetaData/Texture.hpp"

/**

**/
namespace Engine::Asset {
    class TextureLoader : public IAssetLoader<Texture> {
    public:
        std::shared_ptr<Texture> LoadFromFile(const std::string& path, AssetManager& /*assets*/) override;
    };
}
