#pragma once
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace Engine::Scene {

    using json = nlohmann::json;

    enum class SceneType {
        Gui,
        GamePlay,
        GameOver,
        Unknown,
    };

    enum class StackBehaviorMode {
        Exclusive,
        Additive,
        Replace,
        Overlay,
        Unknown,
    };

    struct StackBehaviorDef {
        StackBehaviorMode mode; // exclusive, additive, replace, overlay
        bool updateUnderlay = false;
        bool renderUnderlay = false;
    };

    struct TransitionDef {
        std::string event; // fade_in, fade_out, slide_left, slide_right, etc.
    };

    struct SceneDef {
        std::string sceneId;
        std::string className;
        SceneType sceneType = SceneType::Gui;

        std::string defaultLevelId;
        bool supportsPause = false;

        std::vector<std::string> userSystems;

        StackBehavior stackBehavior;



    };

    struct SceneMeta {
        std::string assetId;
        std::string className;
        std::string category;
        std::string defaultLevelId;
        std::string stackBehavior;
        bool supportsPause = false;
        std::string pauseSceneId;
        
    };
    
    /*inline void from_json(const nlohmann::json& j, SceneMeta& data) {
        j.at("sceneId").get_to(data.sceneId);
        j.at("sceneType").get_to(data.sceneType);
    }*/
} // namespace Engine::Scene
