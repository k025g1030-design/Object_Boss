#include "Engine/Asset/Loader/LevelDataLoader.hpp"
#include "Engine/Asset/AssetsManager.hpp"
#include "Engine/Asset/Data/LevelData.hpp"
#include <memory>
#include <string>
#include "Utils/JSONParser.hpp"

namespace Engine::Asset {
    std::shared_ptr<LevelData> LevelDataLoader::LoadFromFile(const std::string& path, AssetManager&) {
        Utils::json json = Utils::JSONParser::Parse(path);
        auto data = std::make_shared<LevelData>();
        *data = json.get<LevelData>();
        return data;
    }
}

