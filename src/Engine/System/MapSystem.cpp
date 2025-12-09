#include "Engine/System/MapSystem.hpp"
#include "Core/Backend.hpp"
#include "Core/EngineAPI.hpp"

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

    void MapSystem::RenderDecorations(Camera camera) {
        for (const auto& dec : currentMapData_->decorations) {
            Core::Vector2 screenPos = {
                static_cast<float>(dec.x * currentMapData_->tileset->scale.pixelsPerUnit - camera.x),
                static_cast<float>(dec.y * currentMapData_->tileset->scale.pixelsPerUnit - camera.y)
            };
            // Render the tile
            Engine::RenderTile(screenPos, currentMapData_->tileset, dec.tileId);
        }

    }

    void MapSystem::RenderDecorationsNotKey(std::string tileId, Camera camera) {
        for (const auto& dec : currentMapData_->decorations) {
            if (dec.tileId == tileId) {
                continue; // Skip decorations with the specified tileId
            }
            Core::Vector2 screenPos = {
                static_cast<float>(dec.x * currentMapData_->tileset->scale.pixelsPerUnit - camera.x),
                static_cast<float>(dec.y * currentMapData_->tileset->scale.pixelsPerUnit - camera.y)
            };
            // Render the tile
            Engine::RenderTile(screenPos, currentMapData_->tileset, dec.tileId);
        }

    }

    void MapSystem::RenderDecorationsInKey(std::string tileId, Camera camera) {
        for (const auto& dec : currentMapData_->decorations) {
            if (dec.tileId != tileId) {
                continue; // Skip decorations without the specified tileId
            }
            Core::Vector2 screenPos = {
                static_cast<float>(dec.x * currentMapData_->tileset->scale.pixelsPerUnit - camera.x),
                static_cast<float>(dec.y * currentMapData_->tileset->scale.pixelsPerUnit - camera.y)
            };
            // Render the tile
            Engine::RenderTile(screenPos, currentMapData_->tileset, dec.tileId);
        }

    }
}
