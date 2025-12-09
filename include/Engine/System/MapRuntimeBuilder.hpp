#pragma once

#include "Engine/System/MapRuntimeData.hpp"
#include "Engine/Asset/Data/MapData.hpp"   // 你這個檔案

namespace Engine::System {

    /// 專門負責把 Asset::MapData 轉成 MapRuntimeData
    class MapRuntimeBuilder {
    public:
        /// 從 MapData 建立一份 runtime
        /// tileWidth, tileHeight：一格 tile 的像素大小
        static MapRuntimeData BuildFromMapData(
            const Engine::Asset::MapData& src,
            int tileWidth,
            int tileHeight
        );
    };

} // namespace Engine::System
