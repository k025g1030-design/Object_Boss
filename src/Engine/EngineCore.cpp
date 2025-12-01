#include <string>
#include "Engine/EngineCore.hpp"
#include <Engine/Asset/Data/TileSetData.hpp>
#include <Engine/Asset/Data/AnimationData.hpp>

namespace Engine {
    void EngineCore::Init(const std::string& assetCatalogPath) {
        assets_.Initialize(assetCatalogPath);
        assets_.Load<Asset::TileSetData>("data.tileset.map");
        assets_.Load<Asset::AnimationData>("data.sheet.player");
    }



}
