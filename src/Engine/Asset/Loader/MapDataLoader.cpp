#include "Engine/Asset/Loader/MapDataLoader.hpp"
#include "Engine/Asset/AssetsManager.hpp"
#include "Engine/Asset/Data/MapData.hpp"
#include <memory>
#include <string>
#include "Utils/JSONParser.hpp"

namespace Asset {
    std::shared_ptr<MapData> MapDataLoader::LoadFromFile(const std::string& path, AssetManager& assets) {
        path;
        assets;
        //Utils::json json = Utils::JSONParser::Parse(path);
        auto clipData = std::make_shared<MapData>();

        //*clipData = json.get<MapData>();

        return clipData;
    }
}

