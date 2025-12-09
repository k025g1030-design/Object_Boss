#pragma once
#include "Engine/System/Camera.hpp"
#include "Engine/Asset/Data/MapData.hpp"
#include "Core/Math.hpp"
#include "MapRuntimeData.hpp"

namespace Engine::System {

    class MapSystem {
    public:
        void Initialize(Engine::Asset::MapData* mapData);
        void Render(Camera camera);
        void RenderLayer(std::string layerName, Camera camera);
        void RenderDecorations(Camera camera);
        void RenderDecorationsNotKey(std::string tileId, Camera camera);
        void RenderDecorationsInKey(std::string tileId, Camera camera);

        MapRuntimeData* LoadMap(const std::string& assetId);
        MapRuntimeData* LoadMap(Engine::Asset::MapData* mapData);

        MapRuntimeData* GetCurrentMap() { return currentMap_; }

    private:
        Engine::Asset::MapData* mapData_ = nullptr;

        std::unordered_map<std::string, std::unique_ptr<MapRuntimeData>> maps_;
        Engine::System::MapRuntimeData* currentMap_;


        /*Core::Vector2 size_;
        Core::Vector2 sizeInTiles_;*/
    };

}
