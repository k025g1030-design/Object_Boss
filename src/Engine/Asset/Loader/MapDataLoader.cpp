#include "Engine/Asset/Loader/MapDataLoader.hpp"
#include "Engine/Asset/AssetsManager.hpp"
#include "Engine/Asset/Data/MapData.hpp"
#include "Engine/Asset/Data/TileSetData.hpp"
#include <memory>
#include <string>
#include "Utils/JSONParser.hpp"

namespace Asset {
    std::shared_ptr<MapData> MapDataLoader::LoadFromFile(const std::string& path, AssetManager& assets) {
        Utils::json json = Utils::JSONParser::Parse(path);
        auto data = std::make_shared<MapData>();

        *data = json.get<MapData>();
        data->tileset = assets.Load<TileSetData>(data->tilesetId);

        return data;
    }
}

