#pragma once
#include <string>
#include <unordered_map>

namespace Engine::Scene {
    class SceneChangeContext {
    public:
        std::unordered_map<std::string, std::string> values;

        void Set(const std::string& key, const std::string& val) {
            values[key] = val;
        }

        bool Has(const std::string& key) const {
            return values.find(key) != values.end();
        }

        std::string Get(const std::string& key,
            const std::string& defaultValue = "") const {
            auto it = values.find(key);
            return (it == values.end()) ? defaultValue : it->second;
        }

        int GetInt(const std::string& key, int def = 0) const {
            auto it = values.find(key);
            return (it == values.end()) ? def : std::stoi(it->second);
        }

        bool GetBool(const std::string& key, bool def = false) const {
            auto it = values.find(key);
            if (it == values.end()) return def;
            return (it->second == "true" || it->second == "1");
        }
    };
}