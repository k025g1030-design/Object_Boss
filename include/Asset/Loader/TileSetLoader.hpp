#pragma once
#include <string>
#include "Asset/Loader/Meta/IAssetLoader.hpp"
#include "Asset/Data/TileSetData.hpp"

/**

**/
namespace Asset {
    class TileSetLoader : public IAssetLoader<TileSetData> {
    public:
        TileSetData* LoadFromFile(const std::string& path) override {

        }
    };
}
