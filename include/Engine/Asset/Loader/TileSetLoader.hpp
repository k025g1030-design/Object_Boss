#pragma once
#include <string>
#include "Engine/Asset/Loader/Meta/IAssetLoader.hpp"
#include "Engine/Asset/Data/TileSetData.hpp"

/**

**/
namespace Asset {
    class TileSetLoader : public IAssetLoader<TileSetData> {
    public:
        std::shared_ptr<TileSetData> LoadFromFile(const std::string& path, AssetManager& assets) override;
    };
}
