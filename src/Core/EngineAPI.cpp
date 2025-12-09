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

    void RenderTile(const Core::Vector2 position, const Asset::TileSetData* tileSetData, const std::string& tileId) {
        auto bgIt = tileSetData->tiles.find(tileId);
        if (bgIt != tileSetData->tiles.end()) {
            int fullHeight = tileSetData->texture->GetHeight();
            int fullWitdth = tileSetData->texture->GetWidth();
            const Engine::Asset::TileDef& bg = bgIt->second;
            int x = static_cast<int>(position.x);
            int y = static_cast<int>(position.y);
            int w = bg.rect ? bg.rect->w : 0;
            int h = bg.rect ? bg.rect->h : 0;
            int srcX = bg.rect ? bg.rect->x : 0;
            int srcY = bg.rect ? bg.rect->y : 0;
            
            Engine::Backend::DrawSpriteRect(
                x, y, srcX, srcY, w, h,
                tileSetData->texture->GetHandle(),
                (bg.rect ? (float)bg.rect->w / (float)fullWitdth : 1.0f),
                (bg.rect ? (float)bg.rect->h / (float)fullHeight : 1.0f),
                0.0f,
                WHITE
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
