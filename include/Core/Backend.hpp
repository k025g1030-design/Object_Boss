#pragma once
#include <Novice.h>

namespace Engine {
    class Backend {
    public:
        static void Initialize(const char* title, int width, int height);
        static void Finalize();
        
        static int ProcessStatus();

        static void StartFrame();
        static void EndFrame();

        static int LoadTexture(const char* fileName);
        static void UnloadTexture(int textureHandle);

        static int LoadAudio(const char* fileName);

        static void GetHitKeyStateAll(char* keyStateBuf);
        static int CheckHitKey(int keyCode);
        static int IsPressMouse(int buttonNumber);

        static void DrawBox(int x, int y, int w, int h, float angle, unsigned int color, FillMode fillMode);

        static void DrawSpriteRect(
            int destX, int destY, int srcX, int srcY, int srcW, int srcH, int textureHandle,
            float scaleX, float scaleY, float angle, unsigned int color);

        static void PlayAudio(int audioHandle, int loop, float volume);
        static void StopAudio(int audioHandle);




    };
}
