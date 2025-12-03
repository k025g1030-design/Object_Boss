#pragma once
#include <string>
#include "Engine/Asset/Loader/Meta/IAssetLoader.hpp"
#include "Engine/Asset/Data/AnimationData.hpp"

/**

**/
namespace Engine::Asset {
    class AnimationLoader : public IAssetLoader<AnimationData> {
    public:
        std::shared_ptr<AnimationData> LoadFromFile(const std::string& path, AssetManager& assets) override;
    };
}
