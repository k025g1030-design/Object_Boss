#include "Engine/System/MapSystem.hpp"
#include "Core/Backend.hpp"
#include "Core/EngineAPI.hpp"
#include <Engine/System/MapRuntimeBuilder.hpp>

namespace Engine::System {
    MapRuntimeData* MapSystem::LoadMap(const std::string& assetId) {
        // 1. 從 AssetManager 取得 MapData（你已經有 Load<MapData> 類似的東西）
        Engine::Asset::MapData* mapData = Engine::GetCore().GetAssetManager().Load<Engine::Asset::MapData>(assetId);
        if (!mapData) return nullptr;

        return LoadMap(mapData);
    }

    MapRuntimeData* MapSystem::LoadMap(Engine::Asset::MapData* mapData) {

        // 2. 決定 tile 大小
        int tileW = mapData->tileset->scale.pixelsPerUnit;
        int tileH = mapData->tileset->scale.pixelsPerUnit;

        // 3. 用 Builder 轉成 RuntimeData
        MapRuntimeData runtime = Engine::System::MapRuntimeBuilder::BuildFromMapData(*mapData, tileW, tileH);

        // 4. 放到 maps_ 裡
        auto it = maps_.find(mapData->assetId);
        if (it == maps_.end()) {
            auto ptr = std::make_unique<MapRuntimeData>(std::move(runtime));
            MapRuntimeData* raw = ptr.get();
            maps_[mapData->assetId] = std::move(ptr);
            currentMap_ = raw;
            return raw;
        } else {
            it->second = std::make_unique<MapRuntimeData>(std::move(runtime));
            currentMap_ = it->second.get();
            return currentMap_;
        }
    }

    void MapSystem::Initialize(Engine::Asset::MapData* mapData) {
        LoadMap(mapData);
    }

    void MapSystem::Render(Camera camera) {
        for (const auto& layer : currentMap_->visualLayers) {
            // Render this layer
            for (int y = 0; y < currentMap_->height; ++y) {
                for (int x = 0; x < currentMap_->width; ++x) {
                    int tileIndex = y * currentMap_->width + x;
                    int tileId = layer.tiles.at(tileIndex);
                    if (tileId != 0) {
                        // Calculate screen position
                        Core::Vector2 screenPos = {
                            static_cast<float>(x * currentMap_->tileWidth - camera.x),
                            static_cast<float>(y * currentMap_->tileHeight - camera.y)
                        };
                        // Render the tile
                        Engine::RenderTile(screenPos, currentMap_->tileset, layer.name);
                    }
                }
            }
        }
    }
    void MapSystem::RenderLayer(std::string layerName, Camera camera) {
        for (const auto& layer : currentMap_->visualLayers) {
            if (layer.name != layerName) continue;
            // Render this layer
            for (int y = 0; y < currentMap_->height; ++y) {
                for (int x = 0; x < currentMap_->width; ++x) {
                    int tileIndex = y * currentMap_->width + x;
                    int tileId = layer.tiles.at(tileIndex);
                    if (tileId != 0) {
                        // Calculate screen position
                        Core::Vector2 screenPos = {
                            static_cast<float>(x * currentMap_->tileWidth - camera.x),
                            static_cast<float>(y * currentMap_->tileHeight - camera.y)
                        };
                        // Render the tile
                        Engine::RenderTile(screenPos, currentMap_->tileset, layer.name);
                    }
                }
            }
        }
    }

    void MapSystem::RenderDecorations(Camera camera) {
        for (const auto& dec : currentMap_->decorations) {
            Core::Vector2 screenPos = {
                static_cast<float>(dec.x * currentMap_->tileWidth - camera.x),
                static_cast<float>(dec.y * currentMap_->tileHeight - camera.y)
            };
            // Render the tile
            Engine::RenderTile(screenPos, currentMap_->tileset, dec.tileId);
        }

    }

    void MapSystem::RenderDecorationsNotKey(std::string tileId, Camera camera) {
        for (const auto& dec : currentMap_->decorations) {
            if (dec.tileId == tileId) {
                continue; // Skip decorations with the specified tileId
            }
            Core::Vector2 screenPos = {
                static_cast<float>(dec.x * currentMap_->tileWidth - camera.x),
                static_cast<float>(dec.y * currentMap_->tileHeight - camera.y)
            };
            // Render the tile
            Engine::RenderTile(screenPos, currentMap_->tileset, dec.tileId);
        }
    }

    void MapSystem::RenderDecorationsInKey(std::string tileId, Camera camera) {
        for (const auto& dec : currentMap_->decorations) {
            if (dec.tileId != tileId) {
                continue; // Skip decorations with the specified tileId
            }
            Core::Vector2 screenPos = {
                static_cast<float>(dec.x * currentMap_->tileWidth - camera.x),
                static_cast<float>(dec.y * currentMap_->tileHeight - camera.y)
            };
            // Render the tile
            Engine::RenderTile(screenPos, currentMap_->tileset, dec.tileId);
        }
    }
}
