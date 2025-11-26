#pragma once
#include "Engine/Asset/MetaData/Texture.hpp"
#include <vector>
#include <string>
#include <unordered_map>

/**

**/
namespace Asset {
    // SpriteSheet の「画像をどう切ったか」レベル
    struct SpriteSheet {
        Texture* texture;             // どの画像を使うか
        std::vector<Frame> frames;    // 画像をどう切ったか
    };

    // 「どの frame index をどういう順番で使うか」という「動きレベル」
    struct AnimationClip {
        std::vector<int> frameIndices;  // SpriteSheet.frames の index
        float fps = 0.0f;
        bool loop = true;
    };

    // SpriteSheet + 複数の Clip をまとめた「1キャラ分のアニメデータ」
    struct AnimationData {
        SpriteSheet sheet;
        std::unordered_map<std::string, AnimationClip> clips;
    };

}