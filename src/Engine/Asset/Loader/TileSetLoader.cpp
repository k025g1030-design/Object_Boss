#include "Engine/Asset/Loader/TileSetLoader.hpp"
#include "Engine/Asset/AssetsManager.hpp"
#include "Engine/Asset/Data/TileSetData.hpp"
#include "Engine/Asset/MetaData/Texture.hpp"
#include <memory>
#include <string>
#include "Utils/JSONParser.hpp"

namespace Engine::Asset {
    std::shared_ptr<TileSetData> TileSetLoader::LoadFromFile(const std::string& path, AssetManager& assets) {
        // 1. json / csv を読み
        Utils::json json = Utils::JSONParser::Parse(path);
        auto tileSet = std::make_shared<TileSetData>();

        *tileSet = json.get<TileSetData>();
        // 2. AssetManager を介して対応する Texture をロードする
        tileSet->texture = assets.Load<Texture>(tileSet->textureId);
        return tileSet;
    }
}


