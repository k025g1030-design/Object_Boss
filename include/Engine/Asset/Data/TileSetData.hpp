#pragma once
#include <unordered_map>
#include "Engine/Asset/MetaData/Texture.hpp"

/**

**/
namespace Engine::Asset {

    using json = nlohmann::json;

    enum class TileType {
        Empty,      // 
        BlackMist,  // 壁 「黒霧」
        Torii,      // 入口 「鳥居」
        Barrier,    // スキル 「結界」
        Count,
    };

    struct TileDef {
        std::optional<Frame> rect;
        std::optional<GridVector> gridIndex;
        std::string name;
        int unitW = 1;    // 1×1 tile
        int unitH = 1;    // 1×2 unitW=1, unitH=2
    };

    struct TileSetData {
        std::string assetId;
        std::string textureId;
        Texture* texture{ nullptr };
        Grid grid;
        Scale scale;

        // tile ID として使う int に対して、対応する Frame 情報を持つ
        std::unordered_map<std::string, TileDef> tiles;
    };


    // ----------------------------
    //  JSON 変換定義
    // ----------------------------

    // シンプルな構造体はマクロで一気に
    inline void from_json(const json& j, TileDef& tile) {
        tile.gridIndex.reset();
        tile.rect.reset();

        if (j.contains("gridIndex")) {
            GridVector gi;
            j.at("gridIndex").get_to(gi);
            tile.gridIndex = gi;
        }

        if (j.contains("rect")) {
            Frame f;
            j.at("rect").get_to(f);
            tile.rect = f;
        }

        if (j.contains("name")) {
            j.at("name").get_to(tile.name);
        }
  
    }

    // ---- TileSetData 全体 ----
    inline void from_json(const json& j, TileSetData& data) {
        j.at("assetId").get_to(data.assetId);
        j.at("textureId").get_to(data.textureId);

        j.at("scale").get_to(data.scale);

        if (j.contains("grid")) {
            j.at("grid").get_to(data.grid);
        }

        data.tiles.clear();
        const json& tilesObj = j.at("tiles");
        for (auto it = tilesObj.begin(); it != tilesObj.end(); ++it) {
            const std::string& key = it.key();  // "0", "1", "3", ...
            //int id = std::stoi(key);            // int に変換
            TileDef tile = it.value().get<TileDef>();
            data.tiles[key] = std::move(tile);
        }
    }
}
