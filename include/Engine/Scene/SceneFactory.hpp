#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <memory>
#include "Engine/Scene/MetaData/SceneMeta.hpp"
#include "Engine/Scene/SceneChangeParam.hpp"

namespace Engine::Scene {

    class IScene;

    class SceneFactory {
    public:
        using Creator = std::function<std::unique_ptr<IScene>(const SceneDef&, const SceneChangeParam&)>;

        void Register(const std::string& className, Creator creator) {
            creators_[className] = std::move(creator);
        }

        std::unique_ptr<IScene> Create(const SceneDef& def, SceneChangeParam param) const;

    private:
        std::unordered_map<std::string, Creator> creators_;
    };
}

