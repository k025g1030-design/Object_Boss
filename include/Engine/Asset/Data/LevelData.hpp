#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

namespace Engine::Asset {
    using json = nlohmann::json;

    
    struct Ponint {
        int x, y;
    };

    // ----------------------------
    // 個別要素の定義
    // ----------------------------

    struct PlayerSpawn {
        Ponint spawn;  // [x, y]
    };

    struct ActorDef {
        std::string id;
        std::string type;
        Ponint spawn;
        bool show = false;
        std::string facing = "down"; // "up", "down", "left", "right"
        bool enabled = false;
    };

    struct TutorialDef {
        std::string assetId;
        bool enabled = false;
    };

    // script[] 内の 1 コマンド
    struct ScriptCommand {
        std::string type;

        // コマンドごとに使うかどうか違うので optional
        std::optional<std::string> actor;      // "actor": "player", "boss_001" ...
        std::optional<std::string> id;         // "id": "dlg_intro_01", "tutorial_move" ...
        std::optional<std::string> condition;  // "condition": "player_reach", ...
        std::optional<std::string> next;       // "next": "scene_intro_02"

        std::optional<int> x;
        std::optional<int> y;
        std::optional<float> speed;
        std::optional<bool> value;
    };

    // レベル全体
    struct LevelData {
        std::string assetId;
        std::string type;   // "gameplay" , "comic"など
        std::string mapAssetId;
        std::string audioAssetId;

        PlayerSpawn player;
        std::vector<ActorDef> actors;
        TutorialDef tutorial;
        std::vector<ScriptCommand> script;
    };

    // ----------------------------
    // nlohmann::json マッピング
    // ----------------------------

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Ponint, x, y)
    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(PlayerSpawn, spawn)
    
    inline void from_json(const json& j, TutorialDef& def) {
        j.at("assetId").get_to(def.assetId);
        j.at("enabled").get_to(def.enabled);
    }

    inline void from_json(const json& j, ActorDef& actor) {
        j.at("id").get_to(actor.id);
        j.at("type").get_to(actor.type);
        j.at("spawn").get_to(actor.spawn);
        if (j.contains("show")) {
            j.at("show").get_to(actor.show);
        } else {
            actor.show = false;
        }
        if (j.contains("facing")) {
            j.at("facing").get_to(actor.facing);
        } else {
            actor.facing = "down";
        }
        if (j.contains("enabled")) {
            j.at("enabled").get_to(actor.enabled);
        } else {
            actor.enabled = false;
        }
    }
        
    
    inline void from_json(const json& j, ScriptCommand& cmd) {
        j.at("type").get_to(cmd.type);
        if (j.contains("actor")) {
            if (j.at("actor").is_null()) {
                cmd.next = std::nullopt;
            } else {
                cmd.next = j.at("actor").get<std::string>();
            }
        }
        if (j.contains("id")) {
            if (j.at("id").is_null()) {
                cmd.next = std::nullopt;
            } else {
                cmd.next = j.at("id").get<std::string>();
            }
        }
        if (j.contains("condition")) {
            if (j.at("condition").is_null()) {
                cmd.next = std::nullopt;
            } else {
                cmd.next = j.at("condition").get<std::string>();
            }
        }
        if (j.contains("next")) {
            if (j.at("next").is_null()) {
                cmd.next = std::nullopt;
            } else {
                cmd.next = j.at("next").get<std::string>();
            }
        }
        if (j.contains("x")) {
            if (j.at("x").is_null()) {
                cmd.x = std::nullopt;
            } else {
                cmd.x = j.at("x").get<int>();
            }
        }
        if (j.contains("y")) {
            if (j.at("y").is_null()) {
                cmd.y = std::nullopt;
            } else {
                cmd.y = j.at("y").get<int>();
            }
        }
        if (j.contains("speed")) {
            if (j.at("speed").is_null()) {
                cmd.speed = std::nullopt;
            } else {
                cmd.speed = j.at("speed").get<float>();
            }
        }
        if (j.contains("value")) {
            if (j.at("value").is_null()) {
                cmd.value = std::nullopt;
            } else {
                cmd.value = j.at("value").get<bool>();
            }
        }
    }


    // ---- LevelData 全体 ----
    inline void from_json(const json& j, LevelData& data) {
        j.at("assetId").get_to(data.assetId);
        j.at("type").get_to(data.type);
        j.at("mapAssetId").get_to(data.mapAssetId);
        j.at("audioAssetId").get_to(data.audioAssetId);
        j.at("player").get_to(data.player);
        if (j.contains("actors")) {
            j.at("actors").get_to(data.actors);
        } else {
            data.actors.clear();
        }
        if (j.contains("tutorial")) {
            j.at("tutorial").get_to(data.tutorial);
        } else {
            data.tutorial = TutorialDef{};
        }
        if (j.contains("script")) {
            j.at("script").get_to(data.script);
        } else {
            data.script.clear();
        }
    }

}