#include "Engine/Scene/SceneRegistry.hpp"
#include "Utils/JSONParser.hpp"

namespace Engine::Scene {
    void SceneRegistry::LoadFromFile(const std::string& path) {
        // JSONファイルを読み込んでSceneMetaをパースする処理を実装
        Utils::json json = Utils::JSONParser::Parse(path);
        SceneMeta meta = json.get<SceneMeta>();
        for (const auto& sceneDef : meta.scenes) {
            defs_.emplace(sceneDef.sceneId, sceneDef);
        }
    }
    const SceneDef* SceneRegistry::Get(const std::string& sceneId) const {
        auto it = defs_.find(sceneId);
        if (it != defs_.end()) {
            return &it->second;
        }
        return nullptr;
    }

}
