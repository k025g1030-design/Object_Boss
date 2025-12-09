#pragma once
#include "Engine/System/Camera.hpp"
#include "Engine/Asset/Data/MapData.hpp"
#include "Core/Math.hpp"

namespace Engine::System {
    class MapSystem {
    public:
        MapSystem() = default;
        ~MapSystem() = default;
        void Initialize(Engine::Asset::MapData* mapData);
        void Render(Camera camera);
        void RenderLayer(std::string layerName, Camera camera);
    private:
        Engine::Asset::MapData* currentMapData_;
        Core::Vector2 size_;
        Core::Vector2 sizeInTiles_;
    };

}
