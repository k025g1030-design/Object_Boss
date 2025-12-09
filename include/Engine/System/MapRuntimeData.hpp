#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace Engine::Asset {
    struct TileSetData; 
}

namespace Engine::System {

    /// 一張地圖在 Runtime 的世界模型
    /// - 視覺層（visualLayers）用於渲染
    /// - 碰撞層（collisions）用於阻擋移動
    /// - 觸發層（tileTriggers / rectTriggers）用於事件觸發
    class MapRuntimeData {
    public:
        // ====== 子結構定義 ======

        /// 可視圖層：只用於渲染
        struct VisualLayer {
            std::string name;             // e.g. "floor", "walls"
            std::vector<int> tiles;       // size = width * height, 0 = 空
            bool visible = true;          // 可選：方便 debug 用
        };

        /// 裝飾物 / 特殊物件（通常是多格尺寸）
        struct Decoration {
            std::string id;               // e.g. "skill.sui"
            std::string tileId;           // e.g. "skill.tile.sui" → 去 TileSetData 找圖

            int x = 0;                    // tile 座標
            int y = 0;
            int w = 1;                    // 幾格寬
            int h = 1;                    // 幾格高

            // tag 標籤（例："skill", "npc" 等）
            std::vector<std::string> tags;
        };

        /// 單格碰撞資訊
        struct TileCollision {
            bool    solid = false;        // true = 不能進入
            uint8_t type = 0;            // 0 = 無, 1 = 牆, 2 = 水... 由你在 JSON 中定義
        };

        /// 單格觸發器（踩到某一格就觸發）
        struct TileTrigger {
            bool        hasTrigger = false;   // false = 此格沒有觸發器
            uint8_t     type = 0;       // 對應 triggerTypes 的 key（轉成數值存）
            std::string triggerId;            // e.g. "skill.to_sui"
        };

        /// 區域觸發器（矩形區域，例如傳送門）
        struct RectTrigger {
            int x = 0;        // tile 座標
            int y = 0;
            int w = 1;
            int h = 1;

            std::string triggerId;   // e.g. "portal.to_boss_room"

            bool once = false;   // true = 只觸發一次
            bool consumed = false;   // 已觸發過且 once == true
        };

    public:
        // ====== 基本資訊 ======

        std::string assetId;      // map 資源的 id（例如 "data.map.shrine.tutorial"）
        std::string tilesetId;    // 使用的 tileset id

        Asset::TileSetData* tileset = nullptr; // 指向 Asset 層的 TileSetData（非擁有）

        int width = 0;       // tile 數量（X 方向）
        int height = 0;       // tile 數量（Y 方向）
        int tileWidth = 64;      // 每 tile 寬度（像素）
        int tileHeight = 64;      // 每 tile 高度（像素）

        // ====== 視覺相關 ======
        std::vector<VisualLayer> visualLayers;
        std::vector<Decoration>  decorations;

        // ====== 邏輯相關 ======
        // 一格一筆：碰撞資料
        std::vector<TileCollision> collisions;   // size = width * height
        // 一格一筆：單格觸發器
        std::vector<TileTrigger>   tileTriggers; // size = width * height
        // 區域觸發器
        std::vector<RectTrigger>   rectTriggers;

    public:
        // ====== 建構 & 初始化 ======

        MapRuntimeData() = default;

        /// 設定地圖尺寸，並視需要初始化 collisions / tileTriggers
        void SetSize(int mapWidth, int mapHeight, int tWidth, int tHeight) {
            width = mapWidth;
            height = mapHeight;
            tileWidth = tWidth;
            tileHeight = tHeight;
        }

        /// 初始化碰撞陣列（全部設為可走）
        void InitCollisionArray() {
            collisions.clear();
            collisions.resize(static_cast<std::size_t>(width * height));
        }

        /// 初始化 tile 觸發器陣列（全部沒有觸發器）
        void InitTileTriggerArray() {
            tileTriggers.clear();
            tileTriggers.resize(static_cast<std::size_t>(width * height));
        }

        // ====== 座標工具 ======

        /// 判斷 (tx, ty) 是否在地圖範圍內（tile 座標）
        [[nodiscard]] bool InBounds(int tx, int ty) const {
            return (tx >= 0 && ty >= 0 && tx < width && ty < height);
        }

        /// 將 (tx, ty) 轉成一維 index（不做邊界檢查）
        [[nodiscard]] std::size_t Index(int tx, int ty) const {
            return static_cast<std::size_t>(ty) * static_cast<std::size_t>(width)
                + static_cast<std::size_t>(tx);
        }

        // ====== 碰撞查詢 ======

        /// 該格是否為不可走（地圖外一律視為不能走）
        [[nodiscard]] bool IsSolid(int tx, int ty) const {
            if (!InBounds(tx, ty)) return true; // 地圖外 = 牆
            if (collisions.empty()) return false;

            const auto& c = collisions[Index(tx, ty)];
            return c.solid;
        }

        // ====== 單格觸發器查詢 ======

        /// 取得該格上的 TileTrigger（沒有則回傳 nullptr）
        [[nodiscard]] const TileTrigger* GetTileTrigger(int tx, int ty) const {
            if (!InBounds(tx, ty)) return nullptr;
            if (tileTriggers.empty()) return nullptr;

            const auto& t = tileTriggers[Index(tx, ty)];
            return t.hasTrigger ? &t : nullptr;
        }

        // ====== 區域觸發器查詢 ======

        /// 取得「包含此格」的所有 RectTrigger index（通常不會很多）
        [[nodiscard]] std::vector<int> GetRectTriggerIndicesAt(int tx, int ty) const {
            std::vector<int> result;
            for (int i = 0; i < static_cast<int>(rectTriggers.size()); ++i) {
                const auto& r = rectTriggers[static_cast<std::size_t>(i)];
                if (r.consumed && r.once) {
                    continue; // 一次性且已觸發 → 略過
                }
                if (tx >= r.x && tx < r.x + r.w &&
                    ty >= r.y && ty < r.y + r.h) {
                    result.push_back(i);
                }
            }
            return result;
        }

        /// 將指定 index 的 RectTrigger 標記為已消耗（如果是一次性）
        void ConsumeRectTrigger(int index) {
            if (index < 0 || index >= static_cast<int>(rectTriggers.size())) {
                return;
            }
            auto& r = rectTriggers[static_cast<std::size_t>(index)];
            if (r.once) {
                r.consumed = true;
            }
        }
    };

} // namespace Engine::System
