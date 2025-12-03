#include <string>
#include "Engine/EngineCore.hpp"
#include "Engine/Asset/Data/TileSetData.hpp"
#include "Engine/Asset/Data/AnimationData.hpp"
#include "Engine/Asset/Data/MapData.hpp"

namespace Engine {
    void EngineCore::Init(const std::string& assetCatalogPath) {
        assets_.Initialize(assetCatalogPath);
        assets_.Load<Asset::TileSetData>("data.tileset.map");
        assets_.Load<Asset::AnimationData>("data.sheet.player");

        assets_.Load<Asset::MapData>("data.map.shrine.tutorial");
        assets_.Load<Asset::MapData>("data.map.shrine.boss_room");



    }



}
