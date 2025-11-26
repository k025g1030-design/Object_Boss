#pragma once
#include "Engine/Asset/MetaData/Texture.hpp"
#include <unordered_map>

/**

**/
namespace Asset {

    enum TileType {
        Empty,      // 
        BlackMist,  // 壁 「黒霧」
        Torii,      // 入口 「鳥居」
        Barrier,    // スキル 「結界」
        Count,
    };

    struct TilePhysicsRule {
        bool solid = false;
        int damageOnTouch = 0;
        std::string eventId;
    };

    struct TileDef {
        Frame rect;
        GridVector gridIndex;
        TilePhysicsRule collision;
        std::vector<std::string> flags;
    };

    struct TileSetData {
        Texture* texture{ nullptr };
        Grid grid;
        Scale scale;

        // tile ID として使う int に対して、対応する Frame 情報を持つ
        std::unordered_map<int, TileDef> tiles;
    };
}
