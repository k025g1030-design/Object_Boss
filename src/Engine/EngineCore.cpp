#include <string>
#include "Engine/EngineCore.hpp"
#include "Engine/Asset/Data/TileSetData.hpp"
#include "Engine/Asset/Data/AnimationData.hpp"
#include "Engine/Asset/Data/MapData.hpp"
#include "Engine/Asset/Data/LevelData.hpp"
#include "Engine/Scene/SceneRegistry.hpp" 
#include "Engine/Scene/SceneFactory.hpp" 
#include "Game/Scenes/GameScene.hpp"
#include "Game/Scenes/MenuScene.hpp"
#include "Game/Scenes/OverScene.hpp"

namespace Engine {
    void EngineCore::Init(const std::string& assetCatalogPath, const std::string& scenesCatalogPath) {
        // Test 
        assets_.Initialize(assetCatalogPath);
        assets_.Load<Asset::TileSetData>("data.tileset.map");
        assets_.Load<Asset::TileSetData>("data.tileset.ui");
        assets_.Load<Asset::AnimationData>("data.sheet.player");

        assets_.Load<Asset::MapData>("data.map.shrine.tutorial");
        assets_.Load<Asset::MapData>("data.map.shrine.boss_room");

        assets_.Load<Asset::LevelData>("data.level.00");
        assets_.Load<Asset::LevelData>("data.level.01");

        auto registry = std::make_shared<Scene::SceneRegistry>();
        registry->LoadFromFile(scenesCatalogPath);
        auto factory = std::make_shared<Scene::SceneFactory>();
         
        factory->Register("GameScene", [](const Engine::Scene::SceneDef& def, const Engine::Scene::SceneChangeParam param) {
            std::string levelId = param.Get("levelId", def.defaultLevelId);
            auto it = std::make_unique<Game::Scenes::GameScene>();

            it->SetSceneId(def.sceneId);
            return it;
        });
        factory->Register("MenuScene", [](const Engine::Scene::SceneDef& def, const Engine::Scene::SceneChangeParam param) {
            (void)param;
            auto it = std::make_unique<Game::Scenes::MenuScene>();
            it->SetSceneId(def.sceneId);
            return it;
        });
        factory->Register("OverScene", [](const Engine::Scene::SceneDef& def, const Engine::Scene::SceneChangeParam param) {
            std::string levelId = param.Get("result", def.defaultLevelId);
            auto it = std::make_unique<Game::Scenes::OverScene>();
            it->SetSceneId(def.sceneId);
            return it;
        });
        scenes_.Initialize(registry, factory);

        scenes_.ChangeScene("ui.menu");
    }

    void EngineCore::RequestSceneEvent(const std::string& sceneId, const std::string& eventId) {
        scenes_.HandleEvent(sceneId, eventId);
    }

}
