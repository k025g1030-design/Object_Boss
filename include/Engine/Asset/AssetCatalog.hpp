#pragma once
#include <string>
#include <unordered_map>


namespace Asset {
    enum class AssetType {
        Texture,      // PNG, JPG などの画像
        Sound,        // WAV, OGG などの音声
        MapSourceData,     // マップデータ (独自フォーマット)
        MapTiledData,      // Tiled で作成したマップデータ (JSON) 
        ClipData,     // アニメーションと絵の切り取りデータ (JSON)
        TextData,     // 文字表示用のフォントデータ (JSON)
        Unknown
    };
    struct AssetInfo {
        AssetType type;
        std::string group;
        std::string path;
    };


    class AssetCatalog {
    public:
        //
        void Load(const std::string& catalogPath);
        //
        void Add(const std::string& assetId, const AssetInfo& assetInfo);
        //
        AssetInfo Get(const std::string& assetId) const {
            return assets_.at(assetId);
        }

        std::string GetTypeStr(const AssetType type) const {
            std::string result = "Unknown";
            if (type == AssetType::Texture) result = "Texture";
            else if (type == AssetType::Sound) result = "Sound";
            else if (type == AssetType::MapSourceData) result = "MapSourceData";
            else if (type == AssetType::MapTiledData) result = "MapTiledData";
            else if (type == AssetType::ClipData) result = "ClipData";
            else if (type == AssetType::TextData) result = "TextData";
            return result;
        }

    private:
        std::unordered_map<std::string, AssetInfo> assets_;
    };
} // namespace Asset
