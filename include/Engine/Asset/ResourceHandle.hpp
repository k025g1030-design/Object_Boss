#pragma once
#include <string>

/**

**/
namespace Engine::Asset {
    class AssetManager; // 前方宣言

    /** 
      ゲーム側に渡す「高級ハンドル」
        - T は実際の資源型（Texture, Sound, AnimationData など）
        - AssetManager 内のキャッシュには shared_ptr<void> で保持
    **/
    template<typename T>
    class ResourceHandle {
    public:
        ResourceHandle() = default;

        ResourceHandle(AssetManager* manager, const std::string& assetId)
            : manager_(manager), assetId_(assetId) {}

        // 資源を取得（ロード済み前提）
        T* Get() const;

        T* operator->() const { return Get(); }
        T& operator*()  const { return *Get(); }

        bool IsValid() const { return Get() != nullptr; }

        const std::string& GetAssetId() const { return assetId_; }

    private:
        AssetManager* manager_ = nullptr; // 所有しない、ただのポインタ
        std::string   assetId_;
    };
}

