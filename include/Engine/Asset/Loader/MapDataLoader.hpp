#pragma once
#include <string>
#include "Engine/Asset/Loader/Meta/IAssetLoader.hpp"
#include "Engine/Asset/Data/MapData.hpp"

/**

**/
namespace Asset {
    class MapDataLoader : public IAssetLoader<MapData> {
    public:
        std::shared_ptr<MapData> LoadFromFile(const std::string& path, AssetManager& assets) override;
    };
}

