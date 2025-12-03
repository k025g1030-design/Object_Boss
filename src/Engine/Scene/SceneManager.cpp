#include "Engine/Scene/SceneManager.hpp"

namespace Engine::Scene {
    void SceneManager::Register(const std::string& sceneId, std::shared_ptr<IScene> scene) {
        scenes_[sceneId] = scene;
    }

    void SceneManager::ChangeScene(const std::string& sceneId) {
        auto it = scenes_.find(sceneId);
        if (it != scenes_.end()) {
            IScene* next = it->second.get();
            if (next == current_) {
                // 同じシーンなら何もしない
                return;
            }

            if (current_) {
                current_->OnExit();
            }

            if (next) {
                current_ = next;
                current_->OnEnter();
            }
        } else {
            current_ = nullptr;
        }
    }
    void SceneManager::Update(float dt) {
        dt;
        if (current_) {
            current_->Update();
        }
    }
    void SceneManager::Render() {
        if (current_) {
            current_->Render();
        }
    }
} // namespace Scene
