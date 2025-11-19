#pragma once
#include <string>
#include "Asset/Loader/Meta/IAssetLoader.hpp"
#include "Asset/Data/AnimationData.hpp"

/**

**/
namespace Asset {
    class AnimationLoader : public IAssetLoader<AnimationData> {
    public:
        AnimationData* LoadFromFile(const std::string& path) override {

        }
    };
}
