#include "Engine/System/MapSystem.hpp"
#include "Core/Backend.hpp"
#include <Core/EngineAPI.hpp>

namespace Engine::System {
    void MapSystem::Initialize(Engine::Asset::MapData* mapData) {
        currentMapData_ = mapData;
        size_ = {
            static_cast<float>(mapData->width * mapData->tileset->scale.pixelsPerUnit),
            static_cast<float>(mapData->height * mapData->tileset->scale.pixelsPerUnit)
        };
        sizeInTiles_ = {
            static_cast<float>(mapData->width),
            static_cast<float>(mapData->height)
        };
    }
    void MapSystem::Render(Camera camera) {
        for (const auto& layer : currentMapData_->layers) {
            // Render this layer
            for (int y = 0; y < currentMapData_->height; ++y) {
                for (int x = 0; x < currentMapData_->width; ++x) {
                    int tileIndex = y * currentMapData_->width + x;
                    int tileId = layer.data[tileIndex];
                    if (tileId != 0) {
                        // Calculate screen position
                        Core::Vector2 screenPos = {
                            static_cast<float>(x * currentMapData_->tileset->scale.pixelsPerUnit - camera.x),
                            static_cast<float>(y * currentMapData_->tileset->scale.pixelsPerUnit - camera.y)
                        };
                        // Render the tile
                        Engine::RenderTile(screenPos, currentMapData_->tileset, std::to_string(tileId));
                    }
                }
            }
        }

    }
    void MapSystem::RenderLayer(std::string layerName, Camera camera) {
        for (const auto& layer : currentMapData_->layers) {
            if (layer.name == layerName) {
                // Render this layer
                for (int y = 0; y < currentMapData_->height; ++y) {
                    for (int x = 0; x < currentMapData_->width; ++x) {
                        int tileIndex = y * currentMapData_->width + x;
                        int tileId = layer.data[tileIndex];
                        if (tileId != 0) {
                            // Calculate screen position
                            Core::Vector2 screenPos = {
                                static_cast<float>(x * currentMapData_->tileset->scale.pixelsPerUnit - camera.x),
                                static_cast<float>(y * currentMapData_->tileset->scale.pixelsPerUnit - camera.y)
                            };
                            // Render the tile
                            Engine::RenderTile(screenPos, currentMapData_->tileset, layer.name);
                        }
                    }
                }
            }
        }

    }
}
