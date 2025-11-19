#include "Asset/Loader/Meta/SoundLoader.hpp"
#include "Core/Backend.hpp"

namespace Asset {
    std::shared_ptr<Sound> SoundLoader::LoadFromFile(const std::string& path, AssetManager& /*assets*/) {
        int handle = Engine::Backend::LoadAudio(path.c_str());
        
        auto sound = std::make_shared<Sound>();
        sound->SetHandle(handle);
        sound->SetPath(path);
        return sound;
    }
}
