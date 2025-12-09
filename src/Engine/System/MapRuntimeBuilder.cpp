#include "Engine/System/MapRuntimeBuilder.hpp"

#include <string>

namespace Engine::System {

    using namespace Engine::Asset;

    MapRuntimeData MapRuntimeBuilder::BuildFromMapData(
        const MapData& src,
        int tileWidth,
        int tileHeight
    ) {
        MapRuntimeData dst;

        // ---- 基本資訊 ----
        dst.assetId = src.assetId;
        dst.tilesetId = src.tilesetId;
        dst.tileset = src.tileset;     // 只是指標，不負責生命週期

        dst.SetSize(src.width, src.height, tileWidth, tileHeight);

        // 把 collisions / tileTriggers 先清成預設值
        dst.InitCollisionArray();
        dst.InitTileTriggerArray();

        // ---- 處理 layers ----
        const int w = src.width;
        const int h = src.height;
        const std::size_t cellCount = static_cast<std::size_t>(w * h);

        auto inBounds = [w, h](int x, int y) {
            return (x >= 0 && y >= 0 && x < w && y < h);
            };

        auto indexOf = [w](int x, int y) -> std::size_t {
            return static_cast<std::size_t>(y) * static_cast<std::size_t>(w)
                + static_cast<std::size_t>(x);
            };

        for (const MapLayer& layer : src.layers) {
            switch (layer.usage) {

            case LayerUsage::Visual: {
                // ---- 視覺層：只用來畫 ----
                MapRuntimeData::VisualLayer vis;
                vis.name = layer.name;
                vis.tiles = layer.data;   // 直接拷貝（size 應該是 w*h）
                vis.visible = true;
                dst.visualLayers.push_back(std::move(vis));
                break;
            }

            case LayerUsage::Collision: {
                // ---- 碰撞層：0=沒有，其他值→依 collisionTypes 查詢 ----
                if (layer.data.size() != cellCount) {
                    // 資料長度不對就跳過，避免崩潰
                    break;
                }

                for (int y = 0; y < h; ++y) {
                    for (int x = 0; x < w; ++x) {
                        std::size_t idx = indexOf(x, y);
                        int v = layer.data[idx];

                        if (v == 0) {
                            continue; // 0 = 無碰撞
                        }

                        // MapLayer 中 collisionTypes 的 key 是 string（"0","1"...）
                        std::string key = std::to_string(v);
                        auto it = layer.collisionTypes.find(key);
                        if (it == layer.collisionTypes.end()) {
                            continue;
                        }

                        const CollisionInfo& info = it->second;
                        auto& col = dst.collisions[idx];
                        col.type = static_cast<std::uint8_t>(v);
                        col.solid = info.solid;
                    }
                }
                break;
            }

            case LayerUsage::Hazard: {
                // ---- 傷害層：目前 MapRuntimeData 還沒定義 hazard，
                // 你可以日後在 MapRuntimeData 裡新增 Hazard grid。
                // 這裡先留 TODO，或者根據需要暫時無視。
                // 例：依照 layer.data 的數值 * layer.hazardTypes 對應 damage。
                break;
            }

            case LayerUsage::Trigger: {
                // ---- 單格觸發層：0=無觸發，其它值→triggerTypes ----
                if (layer.data.size() != cellCount) {
                    break;
                }

                for (int y = 0; y < h; ++y) {
                    for (int x = 0; x < w; ++x) {
                        std::size_t idx = indexOf(x, y);
                        int v = layer.data[idx];

                        if (v == 0) {
                            continue; // 0 = 無觸發
                        }

                        std::string key = std::to_string(v);
                        auto it = layer.triggerTypes.find(key);
                        if (it == layer.triggerTypes.end()) {
                            // JSON 裡沒有對應 triggerTypes，就當作無觸發
                            continue;
                        }

                        const TriggerInfo& info = it->second;
                        if (info.triggerId.empty()) {
                            continue;
                        }

                        auto& trg = dst.tileTriggers[idx];
                        trg.hasTrigger = true;
                        trg.type = static_cast<std::uint8_t>(v);
                        trg.triggerId = info.triggerId;
                    }
                }
                break;
            }

            default:
                break;
            } // end switch
        } // end for layers

        // ---- 處理矩形區域觸發器（MapData::triggers） ----
        dst.rectTriggers.reserve(src.triggers.size());
        for (const MapTrigger& t : src.triggers) {
            MapRuntimeData::RectTrigger rt;
            rt.x = t.x;
            rt.y = t.y;
            rt.w = t.size.w;
            rt.h = t.size.h;
            rt.triggerId = t.triggerId;
            rt.once = t.once;
            rt.consumed = false;

            dst.rectTriggers.push_back(std::move(rt));
        }

        // ---- 處理裝飾物（MapData::decorations） ----
        dst.decorations.reserve(src.decorations.size());
        for (const Decorations& deco : src.decorations) {
            MapRuntimeData::Decoration d;
            d.id = deco.id;
            d.tileId = deco.tileId;
            d.x = deco.x;
            d.y = deco.y;
            d.w = deco.size.w;
            d.h = deco.size.h;
            d.tags = deco.flags;   // 直接沿用 flags 當作 tags

            dst.decorations.push_back(std::move(d));
        }

        return dst;
    }

} // namespace Engine::System
