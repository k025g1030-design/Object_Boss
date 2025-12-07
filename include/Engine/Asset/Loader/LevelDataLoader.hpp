#pragma once
#include <string>
#include "Engine/Asset/Loader/Meta/IAssetLoader.hpp"
#include "Engine/Asset/Data/LevelData.hpp"

/**

**/
namespace Engine::Asset {
    class LevelDataLoader : public IAssetLoader<LevelData> {
    public:
        std::shared_ptr<LevelData> LoadFromFile(const std::string& path, AssetManager& /*assets*/) override;
    };
}
