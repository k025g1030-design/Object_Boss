#include "Core/EngineAPI.hpp"
#include "Core/Backend.hpp"
#include "Core/Config.hpp"

namespace {
    Engine::EngineCore gEngine_;
}

namespace Engine {
    void Initialize(const std::string& assetCatalogPath, const std::string& scenesCatalogPath) {
        Engine::Backend::Initialize(Core::kWindowTitle, Core::kWindowWidth, Core::kWindowHeight);
        gEngine_.Init(assetCatalogPath, scenesCatalogPath);
    }

    Engine::EngineCore& GetCore() {
        return gEngine_;
    }

    bool MouseLeftClicked() {
        return Engine::Backend::IsPressMouse(Core::MouseButton::LEFT_BUTTON);
    }

    void RenderSprite(const Core::Vector2 position, const Asset::Sprite& sprite) {
        position;
        sprite;
    }

    void GetMousePosition(int* x, int* y) {
        Engine::Backend::GetMousePosition(x, y);
    }

    void RenderText(const Core::Vector2 position, const std::string& text) {
        Engine::Backend::RenderText((int)position.x, (int)position.y, text.c_str());
    }

    void RenderFullScreenQuad(unsigned int color) {
        Engine::Backend::DrawBox(0, 0, Core::kWindowWidth, Core::kWindowHeight, 0, color, kFillModeSolid);
    }

    void RenderAnimation(const Core::Vector2 position, Engine::Asset::Frame frame, const Asset::Texture* texture) {
        int x = static_cast<int>(position.x);
        int y = static_cast<int>(position.y);
        
        Engine::Backend::DrawQuad(
            x, y, frame.w, frame.h,
            frame.x, frame.y, frame.w, frame.h,
            texture->GetHandle()
        );
        
    }

    void RenderTile(const Core::Vector2 position, const Asset::TileSetData* tileSetData, const std::string& tileId) {
        auto bgIt = tileSetData->tiles.find(tileId);
        if (bgIt != tileSetData->tiles.end()) {
            /*int fullHeight = tileSetData->texture->GetHeight();
            int fullWitdth = tileSetData->texture->GetWidth();*/
            const Engine::Asset::TileDef& bg = bgIt->second;
            int unit = tileSetData->scale.pixelsPerUnit;

            int x = static_cast<int>(position.x);
            int y = static_cast<int>(position.y);
            int w, h, srcX, srcY = 0;

            if (bg.gridIndex.has_value()) {
                w = unit;
                h = unit;
                srcX = bg.gridIndex->col * unit;
                srcY = bg.gridIndex->row * unit;
            } else {
                w = bg.rect->w;
                h = bg.rect->h;
                srcX = bg.rect->x;
                srcY = bg.rect->y;
            }

            Engine::Backend::DrawQuad(
                x, y, w, h,
                srcX, srcY, w, h,
                tileSetData->texture->GetHandle()
            );

        }
    }


    

    void RenderAnimetion(const Core::Vector2 position, const Asset::AnimationData& animation) {
        position;
        animation;
    }

    void PlaySound(const Asset::SoundData& soundData) {
        soundData;
    }

    void StopSound(const Asset::SoundData& soundData) {
        soundData;
    }
}
