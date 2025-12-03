#include "Engine/Asset/Loader/AnimationLoader.hpp"
#include "Engine/Asset/AssetsManager.hpp"
#include "Engine/Asset/Data/AnimationData.hpp"
#include "Engine/Asset/MetaData/Texture.hpp"
#include <memory>
#include <string>
#include "Utils/JSONParser.hpp"

namespace Engine::Asset {
    std::shared_ptr<AnimationData> AnimationLoader::LoadFromFile(const std::string& path, AssetManager& assets) {
        Utils::json json = Utils::JSONParser::Parse(path);
        auto clipData = std::make_shared<AnimationData>();

        *clipData = json.get<AnimationData>();
        clipData->texture = assets.Load<Texture>(clipData->textureId);

        return clipData;
    }
}

