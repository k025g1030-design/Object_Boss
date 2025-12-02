#include "Engine/Asset/Loader/SpriteLoader.hpp"
#include "Engine/Asset/AssetsManager.hpp"
#include "Engine/Asset/Data/Sprite.hpp"
#include "Engine/Asset/MetaData/Texture.hpp"
#include <memory>
#include <string>
#include "Utils/JSONParser.hpp"

namespace Asset {
    std::shared_ptr<Sprite> SpriteLoader::LoadFromFile(const std::string& path, AssetManager& assets) {
        
        Utils::json json = Utils::JSONParser::Parse(path);
        auto clipData = std::make_shared<Sprite>();

        *clipData = json.get<Sprite>();
        clipData->texture = assets.Load<Texture>(clipData->textureId);

        return clipData;
    }
}


