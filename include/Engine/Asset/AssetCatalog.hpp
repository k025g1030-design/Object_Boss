#pragma once
#include <string>
#include <unordered_map>


namespace Engine::Asset {
    enum class AssetType {
        Texture,      // PNG, JPG などの画像 (PNG,JPG) (RenderSystem)
        Sound,        // WAV, OGG などの音声 (MP3,WAV) (AudioSystem)
        SpriteSheet,       // 絵の切り取り (JSON) (BG)
        MapSourceData,     // マップデータ (CSV/JSON) (SceneSystem)
        TileSetData,      //  絵の切り取り (JSON) (UI / Item / Map)
        AnimClipData,     // アニメーションと絵の切り取りデータ (JSON) (AnimationSystem)
        LevelData,       // レベル全体のデータ (JSON) (SceneSystem)
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
            else if (type == AssetType::TileSetData) result = "TileSetData";
            else if (type == AssetType::AnimClipData) result = "ClipData";
            else if (type == AssetType::TextData) result = "TextData";
            return result;
        }

    private:
        std::unordered_map<std::string, AssetInfo> assets_;
    };
} // namespace Asset
