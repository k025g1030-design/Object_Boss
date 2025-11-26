#include "Engine/Asset/Loader/TileSetLoader.hpp"
#include "Engine/Asset/AssetsManager.hpp"
#include "Engine/Asset/Data/TileSetData.hpp"
#include "Engine/Asset/MetaData/Texture.hpp"
#include <memory>
#include <string>
#include "Utils/JSONParser.hpp"

namespace Asset {
    std::shared_ptr<TileSetData> TileSetLoader::LoadFromFile(const std::string& path, AssetManager& assets) {
        path;
        assets;
        // 1. 讀 json / csv：這裡用 pseudo-code
        /*ParsedAnimMeta meta = ParseAnimMeta(path);
         meta.textureId = "tex.player";
         meta.frames = {...};
         meta.clips  = {...};*/

        auto tileSet = std::make_shared<TileSetData>();

        // 2. 透過 AssetManager 再去 load 對應的 Texture
        /*Texture* tex = assets.Load<Texture>(meta.textureId);
        anim->sheet.texture = tex;
        anim->sheet.frames = meta.frames;
        anim->clips = meta.clips;*/

        return tileSet;
    }
}


