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
        int unit = tileSet->scale.pixelsPerUnit;
        for (auto& [tileId, tileDef] : tileSet->tiles) {
            // tileId は文字列なので、そのまま使う
            // tileDef は from_json で処理済み
            tileDef.unitW = tileDef.rect.has_value() ? tileDef.rect.value().w / unit : 1;
            tileDef.unitH = tileDef.rect.has_value() ? tileDef.rect.value().h / unit : 1;

            tileDef.unitW = tileDef.unitW < 1  ? 1 : tileDef.unitW;
            tileDef.unitH = tileDef.unitH < 1 ? 1 : tileDef.unitH;
        }
        
        // 2. AssetManager を介して対応する Texture をロードする
        tileSet->texture = assets.Load<Texture>(tileSet->textureId);
        return tileSet;
    }
}


