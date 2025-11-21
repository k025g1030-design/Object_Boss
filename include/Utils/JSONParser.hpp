#pragma once
#include <nlohmann/json.hpp>
#include <fstream> 

namespace Utils {
    using json = nlohmann::json;

    class JSONParser {
    public:
        static json ParseFromFile(const std::string& filePath) {
            std::ifstream file(filePath);
            if (!file.is_open()) {
                throw std::runtime_error("Could not open JSON file: " + filePath);
            }
            json jsonData = json::parse(file);
            file.close();
            return jsonData;
        }
    };
}
