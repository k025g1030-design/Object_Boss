#pragma once
#include <string>
#include "Engine/Asset/Loader/Meta/IAssetLoader.hpp"
#include "Engine/Asset/MetaData/Sound.hpp"

/**

**/
namespace Engine::Asset {
    class SoundLoader : public IAssetLoader<Sound> {
    public:
        std::shared_ptr<Sound> LoadFromFile(const std::string& path, AssetManager& /*assets*/) override;
    };
}
