#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include "Engine/Asset/Data/TileSetData.hpp"
/**

**/
namespace Engine::Asset {

    using json = nlohmann::json;

    enum class LayerUsage {
        Visual,
        Collision,
        Hazard,
        Trigger
    };

    struct Size {
        int w, h;   
    };

    struct CollisionInfo {
        bool solid = false;
    };

    struct HazardInfo {
        float damage = 0.0f;
    };

    struct TriggerInfo {
        std::string triggerId;  // "portal.to_stage3" など
    };

    struct MapLayer {
        std::string name;
        LayerUsage usage = LayerUsage::Visual;

        /*int width = 0;
        int height = 0;*/
        std::vector<int> data;  // size = width * height, 0=empty

        // for visual layer
        std::vector<std::string> flags;  // ["floor","fire"] など

        // for collision layer
        std::unordered_map<std::string, CollisionInfo> collisionTypes;

        // for hazard layer
        std::unordered_map<std::string, HazardInfo> hazardTypes;

        // for trigger layer
        std::unordered_map<std::string, TriggerInfo> triggerTypes;
    };

    struct MapTrigger {
        int x = 0;
        int y = 0;
        Size size{ 0, 0 };
        std::string triggerId;              // "cutscene.boss_intro"
        bool once = true;
        // params: std::unordered_map<string, string>
    };

    struct Decorations {
        std::string id;
        std::string tileId;
        int x = 0;
        int y = 0;
        Size size{ 0, 0 };
        std::vector<std::string> flags;
    };

    


    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Size,
        w,
        h
    )

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(CollisionInfo,
        solid
    )
    
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(HazardInfo,
        damage
    )


    struct MapData {
        std::string assetId;
        std::string tilesetId;

        TileSetData* tileset{ nullptr };;

        int width = 0;
        int height = 0;

        // TODO: layers を map<string, MapLayer> にする？
        std::vector<MapLayer> layers;
        std::vector<MapTrigger> triggers;

        std::vector<Decorations> decorations;
    };

    inline void ExtractRegionsToDecorations(
        MapData& map,
        const std::string& layerName,
        int regionTileId,
        const std::string& decoTileId,                // tileset 中的大圖 id
        const std::string& decoIdPrefix,              // 生成用前綴，例如 "portal.region"
        const std::vector<std::string>& flags = {}    // 例如 {"portal"}
    ) {
        // 找到指定 layer
        MapLayer* layerPtr = nullptr;
        for (auto& layer : map.layers) {
            if (layer.name == layerName) {
                layerPtr = &layer;
                break;
            }
        }
        if (!layerPtr) return;

        MapLayer& layer = *layerPtr;
        const int w = map.width;
        const int h = map.height;
        auto& tiles = layer.data;

        if ((int)tiles.size() != w * h) {
            // 資料長度不對就不處理
            return;
        }

        std::vector<bool> visited(w * h, false);
        auto idx = [w](int x, int y) { return y * w + x; };

        int regionCount = 0;

        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                const int i = idx(x, y);
                const int v = tiles[i];
                if (v != regionTileId) continue;
                if (visited[i])       continue;

                // 往右擴展
                int xmax = x;
                while (xmax + 1 < w && tiles[idx(xmax + 1, y)] == regionTileId)
                    ++xmax;

                // 往下擴展
                int ymax = y;
                bool ok = true;
                while (ok && ymax + 1 < h) {
                    for (int xx = x; xx <= xmax; ++xx) {
                        if (tiles[idx(xx, ymax + 1)] != regionTileId) {
                            ok = false;
                            break;
                        }
                    }
                    if (ok) ++ymax;
                }

                // 生成 Decoration
                Decorations deco;
                deco.id = decoIdPrefix + "." + std::to_string(regionCount++);
                deco.tileId = decoTileId;
                deco.x = x;
                deco.y = y;
                deco.size = Size{ xmax - x + 1, ymax - y + 1 };
                deco.flags = flags;

                map.decorations.push_back(std::move(deco));

                // 標記 visited + 清空 tiles
                for (int yy = y; yy <= ymax; ++yy) {
                    for (int xx = x; xx <= xmax; ++xx) {
                        const int j = idx(xx, yy);
                        visited[j] = true;
                        tiles[j] = 0; // 清成 0，避免同時再當普通 tile 用
                    }
                }
            }
        }
    }

    inline void from_json(const json& j, TriggerInfo& info) {
        if (j.contains("triggerId")) {
            j.at("triggerId").get_to(info.triggerId);
        }
    }


    inline void from_json(const json& j, MapLayer& layer) {
        layer.name = j.at("name").get<std::string>();
        std::string usageStr = j.at("usage").get<std::string>();

        for (auto& c : usageStr) {
            c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }
        if (usageStr == "visual") {
            layer.usage = LayerUsage::Visual;
        } else if (usageStr == "collision") {
            layer.usage = LayerUsage::Collision;
        } else if (usageStr == "hazard") {
            layer.usage = LayerUsage::Hazard;
        } else if (usageStr == "trigger") {
            layer.usage = LayerUsage::Trigger;
        }

        /*layer.width = j.at("width").get<int>();
        layer.height = j.at("height").get<int>();*/
        j.at("data").get_to(layer.data);

        if (j.contains("flags")) {
            j.at("flags").get_to(layer.flags);
        } else {
            layer.flags.clear();
        }

        if (j.contains("collisionTypes")) {
            const json& collObj = j.at("collisionTypes");
            for (auto it = collObj.begin(); it != collObj.end(); ++it) {
                const std::string& key = it.key();
                CollisionInfo info = it.value().get<CollisionInfo>();
                layer.collisionTypes[key] = std::move(info);
            }
        } else {
            layer.collisionTypes.clear();
        }

        if (j.contains("hazardTypes")) {
            const json& collObj = j.at("hazardTypes");
            for (auto it = collObj.begin(); it != collObj.end(); ++it) {
                const std::string& key = it.key();
                HazardInfo info = it.value().get<HazardInfo>();
                layer.hazardTypes[key] = std::move(info);
            }
        } else {
            layer.hazardTypes.clear();
        }

        if (j.contains("triggerTypes")) {
            const json& trigObj = j.at("triggerTypes");
            for (auto it = trigObj.begin(); it != trigObj.end(); ++it) {
                TriggerInfo info = it.value().get<TriggerInfo>();
                if (!info.triggerId.empty()) {
                    layer.triggerTypes[it.key()] = std::move(info);
                }
            }
        } else {
            layer.triggerTypes.clear();
        }
        
    }

    inline void from_json(const json& j, MapTrigger& trigger) {
        j.at("x").get_to(trigger.x);
        j.at("y").get_to(trigger.y);
        j.at("size").get_to(trigger.size);
        if (j.contains("triggerId")) {
            j.at("triggerId").get_to(trigger.triggerId);
        }   
        if (j.contains("once")) {
            j.at("once").get_to(trigger.once);
        } else {
            trigger.once = true;
        }
    }

    inline void from_json(const json& j, Decorations& deco) {
        j.at("id").get_to(deco.id);
        j.at("tileId").get_to(deco.tileId);
        j.at("x").get_to(deco.x);
        j.at("y").get_to(deco.y);
        j.at("size").get_to(deco.size);
        if (j.contains("flags")) {
            j.at("flags").get_to(deco.flags);
        } else {
            deco.flags.clear();
        }
    }

    // ---- MapData 全体 ----
    inline void from_json(const json& j, MapData& data) {
        j.at("assetId").get_to(data.assetId);
        j.at("tilesetId").get_to(data.tilesetId);

        j.at("width").get_to(data.width);
        j.at("height").get_to(data.height);

        if (j.contains("layers")) {
            const json& tilesObj = j.at("layers");
            for (auto it = tilesObj.begin(); it != tilesObj.end(); ++it) {
                MapLayer layer = it.value().get<MapLayer>();
                data.layers.push_back(std::move(layer));
            }
        } else {
            data.layers.clear();
        }

        if (j.contains("triggers")) {
            const json& triggersObj = j.at("triggers");
            for (auto it = triggersObj.begin(); it != triggersObj.end(); ++it) {
                MapTrigger trigger = it.value().get<MapTrigger>();
                data.triggers.push_back(std::move(trigger));
            }
        } else {
            data.triggers.clear();
        }


        if (j.contains("decorations")) {
            const json& decosObj = j.at("decorations");
            for (auto it = decosObj.begin(); it != decosObj.end(); ++it) {
                Decorations deco = it.value().get<Decorations>();
                data.decorations.push_back(std::move(deco));
            }
        } else {
            data.decorations.clear();
        }
    }
}

