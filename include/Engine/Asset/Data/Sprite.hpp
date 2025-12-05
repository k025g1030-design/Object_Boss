#pragma once
#include "Engine/Asset/MetaData/Texture.hpp"
#include <string>

/**

**/
namespace Engine::Asset {

    using json = nlohmann::json;

    struct Sprite {
        std::string assetId;
        std::string textureId;
        Texture* texture;
        Frame frame;
    };

    // ---- Sprite 全体 ----
    inline void from_json(const json& j, Sprite& data) {
        j.at("assetId").get_to(data.assetId);
        j.at("textureId").get_to(data.textureId);

        if (j.contains("frame")) {
            j.at("frame").get_to(data.frame);
        }
    }
}

