#include "Engine/Asset/AssetCatalog.hpp"
#include "Utils/CSVParser.hpp"

using namespace Utils;

namespace Asset {
    void AssetCatalog::Load(const std::string& catalogPath) {
        // Implementation to load asset catalog from a file
        // This is a placeholder implementation
        auto csv = CSVParser::Parse(catalogPath);
        for (const auto& row : csv) {
            // Example: parse row to AssetInfo and add to catalog
            // Assuming row[0]=assetId, row[1]=type, row[2]=group, row[3]=path
            std::string assetId = "";
            std::string group = "";
            std::string path = "";
            AssetType type = AssetType::Unknown;
            if (!row.empty()) {
                assetId = row[0];
                if (row.size() > 1) {
                    if (row[1] == "Texture") type = AssetType::Texture;
                    else if (row[1] == "Sound") type = AssetType::Sound;
                    else if (row[1] == "MapTiledData") type = AssetType::MapTiledData;
                    else if (row[1] == "ClipData") type = AssetType::ClipData;
                    else if (row[1] == "TextData") type = AssetType::TextData;
                }
                group = row.size() > 2 ? row[2] : "";
                group = row.size() > 3 ? row[3] : "";
                Add(assetId, {
                    type,
                    group,
                    path
                });
            }
            
        }
    }

    void AssetCatalog::Add(const std::string& assetId, const AssetInfo& assetInfo) {
        // Implementation to add an asset to the catalog
        // This is a placeholder implementation
        assets_[assetId] = assetInfo;
    }
}
