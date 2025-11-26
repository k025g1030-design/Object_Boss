#pragma once
#include <string>
#include "Engine/Asset/AssetsManager.hpp"

/**
  [内部]エンジンのコア機能をまとめたクラス
**/
namespace Engine {
    class EngineCore {
    public:
        void Init(const std::string& catalogPath);

        Asset::AssetManager& GetAssetManager() { return assets_; }

    private:
        Asset::AssetManager assets_;
        //RenderSystem render_;
        // ...
    };


}