#include "Engine/Scene/SceneFactory.hpp"
#include "Engine/Scene/IScene.hpp"
#include <cassert>

namespace Engine::Scene {
    std::unique_ptr<IScene> SceneFactory::Create(const SceneDef& def, SceneChangeParam param) const {
        auto it = creators_.find(def.className);
        if (it == creators_.end()) {
            assert(false && "SceneFactory: unknown className");
            return nullptr;
        }
        auto scene = (it->second)(def, param);
        if (scene) {
            scene->SetSceneId(def.sceneId);
        }
        return scene;
    }
}
