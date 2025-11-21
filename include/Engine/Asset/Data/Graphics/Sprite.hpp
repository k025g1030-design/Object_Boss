#pragma once
#include "Engine/Asset/MetaData/Texture.hpp"
#include "Core/Math.hpp"

/**

**/
namespace Asset {

    struct Sprite {
        Texture* texture{ nullptr };
        Frame frame;
        Core::Vector2 scale{ 1.0f, 1.0f };
    };
}

