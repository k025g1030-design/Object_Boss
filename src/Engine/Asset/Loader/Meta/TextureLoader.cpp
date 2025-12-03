#include <memory>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Engine/Asset/Loader/Meta/TextureLoader.hpp"
#include "Core/Backend.hpp"

namespace Engine::Asset {
    std::shared_ptr<Texture> TextureLoader::LoadFromFile(const std::string& path, AssetManager&) {
        int w = 0, h = 0, comp = 0;
        unsigned char* pixels = stbi_load(path.c_str(), &w, &h, &comp, 4); // RGBA
        if (!pixels) {
            return nullptr;
        }
        int handle = Engine::Backend::LoadTexture(path.c_str()); 

        auto tex = std::make_shared<Texture>();
        tex->SetHandle(handle);
        tex->SetWidth(w);
        tex->SetHeight(h);

        stbi_image_free(pixels); 

        return tex;
    }


}

