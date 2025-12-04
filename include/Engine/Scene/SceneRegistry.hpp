#pragma once
#include <string>
#include <unordered_map>
#include "Engine/Scene/MetaData/SceneMeta.hpp"

namespace Engine::Scene {
    class SceneRegistry {
    public:
        void LoadFromFile(const std::string& path);

        const SceneDef* Get(const std::string& sceneId) const;

    private:
        // sceneId : SceneDef
        std::unordered_map<std::string, SceneDef> defs_;
    };
}