#pragma once
#include <string>
#include <unordered_map>

namespace Asset {
    enum class AssetType {
        Texture,
        Sound,
        MapTiled,
        Skill,
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
        void Add(const AssetInfo& assetInfo);
        //
        AssetInfo Get(const std::string& id) const {
            return assets_.at(id);
        }

    private:
        std::unordered_map<std::string, AssetInfo> assets_;
    };
} // namespace Asset
