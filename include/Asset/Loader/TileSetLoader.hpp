#pragma once
#include <string>
#include "Asset/Loader/Meta/IAssetLoader.hpp"
#include "Asset/Data/TileSetData.hpp"

/**

**/
namespace Asset {
    class TileSetLoader : public IAssetLoader<TileSetData> {
    public:
        std::shared_ptr<TileSetData> LoadFromFile(const std::string& path, AssetManager& assets) override;
    };
}
