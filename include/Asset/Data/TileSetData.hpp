#pragma once
#include "Asset/MetaData/Texture.hpp"
#include <unordered_map>

/**

**/
namespace Asset {

    enum TileType {
        Empty,
        BlackMist,  // 壁
        Torii,      // 入口
        Barrier,    // スキル
        Count,
    };

    struct TileSetData {
        Texture* texture{ nullptr };
        int tileWidth{ 0 };
        int tileHeight{ 0 };

        // tile ID として使う int に対して、対応する Frame 情報を持つ
        std::unordered_map<int, Frame> map;
    };
}
