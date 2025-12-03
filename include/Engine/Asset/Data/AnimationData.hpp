#pragma once
#include "Engine/Asset/MetaData/Texture.hpp"
#include <vector>
#include <string>
#include <unordered_map>

/**

**/
namespace Engine::Asset {
    using json = nlohmann::json;

    // 「どの frame index をどういう順番で使うか」という「動きレベル」
    struct AnimationClip {
        std::vector<int> frameIndices;  // SpriteSheet.frames の index
        float fps = 0.0f;
        int speed = 5;
    };

    // SpriteSheet の「画像をどう切ったか」レベル
    struct AnimationData {
        std::string assetId;
        std::string textureId;
        Texture* texture;             // どの画像を使うか
        Grid grid;
        Scale scale;

        std::vector<Frame> frames;    // 画像をどう切ったか

        std::unordered_map<std::string, AnimationClip> clips;
    };    

    

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(AnimationClip,
        frameIndices,
        fps,
        speed
    )

    // ---- AnimationData 全体 ----
    inline void from_json(const json& j, AnimationData& data) {
        j.at("assetId").get_to(data.assetId);
        j.at("textureId").get_to(data.textureId);

        j.at("scale").get_to(data.scale);
        if (j.contains("grid")) {
            j.at("grid").get_to(data.grid);
        }

        if (j.contains("frames")) {
            j.at("frames").get_to(data.frames);
        }

        data.clips.clear();
        const json& clipsObj = j.at("clips");
        for (auto it = clipsObj.begin(); it != clipsObj.end(); ++it) {
            AnimationClip clip = it.value().get<AnimationClip>();
            data.clips[it.key()] = std::move(clip);
        }
    }

}