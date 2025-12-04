#pragma once
#include <string>
#include "Engine/Asset/AssetsManager.hpp"
#include "Engine/Scene/SceneManager.hpp"

/**
  [内部]エンジンのコア機能をまとめたクラス
**/
namespace Engine {
    class EngineCore {
    public:
        void Init(const std::string& catalogPath, const std::string& scenesCatalogPath);

        Asset::AssetManager& GetAssetManager() { return assets_; }
        Scene::SceneManager& GetSceneManager() { return scenes_; }

    private:
        Asset::AssetManager assets_;
        Scene::SceneManager scenes_;
        //RenderSystem render_;
        // ...
    };


}