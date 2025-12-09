#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <memory>
#include "Engine/Scene/MetaData/SceneMeta.hpp"
#include "Engine/Scene/SceneChangeContext.hpp"

namespace Engine::Scene {

    class IScene;

    class SceneFactory {
    public:
        using Creator = std::function<std::unique_ptr<IScene>(const SceneDef&, const SceneChangeContext&)>;

        void Register(const std::string& className, Creator creator) {
            creators_[className] = std::move(creator);
        }

        std::unique_ptr<IScene> Create(const SceneDef& def, SceneChangeContext ctx) const;

    private:
        std::unordered_map<std::string, Creator> creators_;
    };
}

