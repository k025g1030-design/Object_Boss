#pragma once
#include <string>
#include "Asset/Loader/Meta/IAssetLoader.hpp"
#include "Asset/MetaData/Sound.hpp"

/**

**/
namespace Asset {
    class SoundLoader : public IAssetLoader<Sound> {
    public:
        std::shared_ptr<Sound> LoadFromFile(const std::string& path, AssetManager& /*assets*/) override;
    };
}
