#pragma once
#include "Engine/Asset/MetaData/Sound.hpp"

/**

**/
namespace Engine::Asset {
    struct SoundData {
        Sound* sound{ nullptr };
        bool loop{ false };
        float volume{ 1.0f };
    };
}