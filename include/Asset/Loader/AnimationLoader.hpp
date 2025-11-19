#pragma once
#include <string>
#include "Asset/Loader/Meta/IAssetLoader.hpp"
#include "Asset/Data/AnimationData.hpp"

/**

**/
namespace Asset {
    class AnimationLoader : public IAssetLoader<AnimationData> {
    public:
        std::shared_ptr<AnimationData> LoadFromFile(const std::string& path, AssetManager& assets) override;
    };
}
