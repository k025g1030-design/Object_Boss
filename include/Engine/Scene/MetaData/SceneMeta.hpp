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
        std::string eventId; // fade_in, fade_out, slide_left, slide_right, etc.
        std::optional<std::string> targetSceneId;
        std::optional<std::string> levelId; // optional, if the transition involves loading a new level
    };

    struct SceneDef {
        std::string sceneId;
        std::string className;
        SceneType sceneType = SceneType::Gui;

        std::string defaultLevelId;
        bool supportsPause = false;

        std::vector<std::string> userSystems;
        StackBehaviorDef stackBehavior;
        std::vector<TransitionDef> transitions;
    };

    struct SceneMeta {
        std::string assetId;
        std::vector<SceneDef> scenes;
    };

    inline void from_json(const json& j, TransitionDef& data) {
        if (j.contains("eventId") && !j.at("eventId").empty()) {
            j.at("eventId").get_to(data.eventId);
        }
        if (j.contains("targetSceneId")) {
            if (j.at("targetSceneId").is_null()) {
                data.targetSceneId = std::nullopt;
            } else {
                data.targetSceneId = j.at("targetSceneId").get<std::string>();
            }
        }
        if (j.contains("levelId") && !j.at("levelId").empty()) {
            if (j.at("levelId").is_null()) {
                data.levelId = std::nullopt;
            } else {
                data.levelId = j.at("levelId").get<std::string>();
            }
        }
    }

    inline void from_json(const json& j, StackBehaviorDef& data) {
        std::string modeStr;
        j.at("mode").get_to(modeStr);
        if (modeStr == "exclusive") {
            data.mode = StackBehaviorMode::Exclusive;
        } else if (modeStr == "additive") {
            data.mode = StackBehaviorMode::Additive;
        } else if (modeStr == "replace") {
            data.mode = StackBehaviorMode::Replace;
        } else if (modeStr == "overlay") {
            data.mode = StackBehaviorMode::Overlay;
        } else {
            data.mode = StackBehaviorMode::Unknown;
        }
        if (j.contains("updateUnderlay")) {
            j.at("updateUnderlay").get_to(data.updateUnderlay);
        } else {
            data.updateUnderlay = false;
        }
        if (j.contains("renderUnderlay")) {
            j.at("renderUnderlay").get_to(data.renderUnderlay);
        } else {
            data.renderUnderlay = false;
        }

    }

    inline void from_json(const json& j, SceneDef& data) {
        j.at("sceneId").get_to(data.sceneId);
        j.at("className").get_to(data.className);
        std::string typeStr;
        j.at("sceneType").get_to(typeStr);
        if (typeStr == "gui") {
            data.sceneType = SceneType::Gui;
        } else if (typeStr == "gameplay") {
            data.sceneType = SceneType::GamePlay;
        } else if (typeStr == "gameover") {
            data.sceneType = SceneType::GameOver;
        } else {
            data.sceneType = SceneType::Unknown;
        }
        if (j.contains("defaultLevelId") && !j.at("defaultLevelId").empty()) {
            j.at("defaultLevelId").get_to(data.defaultLevelId);
        } else {
            data.defaultLevelId = "";
        }
        if (j.contains("supportsPause")) {
            j.at("supportsPause").get_to(data.supportsPause);
        } else {
            data.supportsPause = false;
        }
        if (j.contains("userSystems")) {
            j.at("userSystems").get_to(data.userSystems);
        } else {
            data.userSystems.clear();
        }
        if (j.contains("stackBehavior")) {
            j.at("stackBehavior").get_to(data.stackBehavior);
        } else {
            data.stackBehavior = StackBehaviorDef{};
        }
        if (j.contains("transitions")) {
            const json& transObj = j.at("transitions");
            for (auto it = transObj.begin(); it != transObj.end(); ++it) {
                TransitionDef tra = it.value().get<TransitionDef>();
                data.transitions.push_back(std::move(tra));
            }
        } else {
            data.transitions.clear();
        }
    }
    
    // ---- SceneMeta 全体 ----
    inline void from_json(const json& j, SceneMeta& data) {
        j.at("assetId").get_to(data.assetId);
        j.at("scenes").get_to(data.scenes);
    }
} // namespace Engine::Scene
