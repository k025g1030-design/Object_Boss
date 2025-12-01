#pragma once
#include "Engine/Asset/MetaData/Texture.hpp"
#include "Core/Math.hpp"

/**

**/
namespace Asset {

    struct Sprite {
        std::string assetId;
        std::string textureId;
        Texture* texture{ nullptr };
        Frame frame;
    };

}

