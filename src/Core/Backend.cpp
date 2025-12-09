#include "Core/Backend.hpp"
#include <string>

namespace Engine {
    void Backend::Initialize(const char* title, int width, int height) {
        Novice::Initialize(title, width, height);
    }
    void Backend::Finalize() {
        Novice::Finalize();
    }
    
    int Backend::ProcessStatus() {
        return Novice::ProcessMessage();
    }

    void Backend::StartFrame() {
        Novice::BeginFrame();
    }

    void Backend::EndFrame() {
        Novice::EndFrame();
    }

    int Backend::LoadTexture(const char* fileName) {
        // Fix: Use std::string to concatenate, then pass c_str() to Novice::LoadTexture
        std::string path = "./";
        path += fileName;
        return Novice::LoadTexture(path.c_str());
    }

    void Backend::UnloadTexture(int textureHandle) {
        Novice::UnloadTexture(textureHandle);
    }

    int Backend::LoadAudio(const char* fileName) {
        std::string path = "./";
        path += fileName;
        return Novice::LoadAudio(fileName);
    }

    void Backend::GetHitKeyStateAll(char* keyStateBuf) {
        Novice::GetHitKeyStateAll(keyStateBuf);
    }

    int Backend::CheckHitKey(int keyCode) {
        return Novice::CheckHitKey(keyCode);
    }

    int Backend::IsPressMouse(int buttonNumber) {
        return Novice::IsPressMouse(buttonNumber);
    }

    void Backend::GetMousePosition(int* x, int* y) {
        Novice::GetMousePosition(x, y);
    }

    void Backend::RenderText(int x, int y, const char* text) {
        Novice::ScreenPrintf(x, y, text);
    }

    void Backend::DrawBox(int x, int y, int w, int h, float angle, unsigned int color, FillMode fillMode) {
        Novice::DrawBox(x, y, w, h, angle, color, fillMode);
    }


    void Backend::DrawQuad(int x, int y, int w, int h, int srcX, int srcY, int srcW, int srcH, int textureHandle) {
        int ltX = x;
        int ltY = y;
        int rtX = x + w;
        int rtY = y;
        int lbX = x;
        int lbY = y + h;
        int rbX = x + w;
        int rbY = y + h;
        Novice::DrawQuad(ltX, ltY, rtX, rtY, lbX, lbY, rbX, rbY, srcX, srcY, srcW, srcH, textureHandle, WHITE);
    }

    void Backend::DrawSpriteRect(
        int destX, int destY, int srcX, int srcY, int srcW, int srcH, int textureHandle,
        float scaleX, float scaleY, float angle, unsigned int color) {
        Novice::DrawSpriteRect(destX, destY, srcX, srcY, srcW, srcH, textureHandle,
            scaleX, scaleY, angle, color);
    }

    void Backend::PlayAudio(int audioHandle, int loop, float volume) {
        Novice::PlayAudio(audioHandle, loop, volume);
    }
    void Backend::StopAudio(int audioHandle) {
        Novice::StopAudio(audioHandle);
    }

}
