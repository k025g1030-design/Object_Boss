#pragma once
#include <string>
#include "Engine/Asset/Loader/Meta/IAssetLoader.hpp"
#include "Engine/Asset/Data/Sprite.hpp"

/**

**/
namespace Asset {
    class SpriteLoader : public IAssetLoader<Sprite> {
    public:
        std::shared_ptr<Sprite> LoadFromFile(const std::string& path, AssetManager& assets) override;
    };
}


