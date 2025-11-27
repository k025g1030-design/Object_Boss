#include <string>
#include "Engine/EngineCore.hpp"

namespace Engine {
    void EngineCore::Init(const std::string& assetCatalogPath) {
        assets_.Initialize(assetCatalogPath);
    }



}
