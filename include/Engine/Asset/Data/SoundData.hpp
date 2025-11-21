#pragma once
#include "Engine/Asset/MetaData/Sound.hpp"

/**

**/
namespace Asset {
    struct SoundData {
        Sound* sound{ nullptr };
        bool loop{ false };
        float volume{ 1.0f };
    };
}