#pragma once
#include <string>
#include "Engine/Asset/AssetsManager.hpp"
#include "Engine/Scene/SceneManager.hpp"
#include "Engine/System/InputSystem.hpp"
#include "Engine/System/GuiSystem.hpp"
#include "Engine/System/MapSystem.hpp"
#include "Engine/System/ActorSystem.hpp"

/**
  [内部]エンジンのコア機能をまとめたクラス
**/
namespace Engine {
    class EngineCore {
    public:
        void Init(const std::string& catalogPath, const std::string& scenesCatalogPath);

        void RequestSceneEvent(const std::string& sceneId, const std::string& eventId);

        Asset::AssetManager& GetAssetManager() { return assets_; }
        Scene::SceneManager& GetSceneManager() { return scenes_; }

        System::InputSystem& GetInputSystem() { return inputSystem_; }
        System::ActorSystem& GetActorSystem() { return actorSystem_; }
        System::GuiSystem& GetGuiSystem() { return guiSystem_; }
        System::MapSystem& GetMapSystem() { return mapSystem_; }

    private:
        Asset::AssetManager assets_;
        Scene::SceneManager scenes_;

        // TODO: 一時的にここで管理するが、将来的には別の方法を検討
        System::InputSystem inputSystem_;
        System::ActorSystem actorSystem_;
        System::GuiSystem guiSystem_;
        System::MapSystem mapSystem_;

        
    };


}