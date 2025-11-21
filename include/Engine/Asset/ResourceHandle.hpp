#pragma once
#include <string>

/**

**/
namespace Asset {
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

        ResourceHandle(AssetManager* manager, const std::string& id)
            : manager_(manager), id_(id) {}

        // 資源を取得（ロード済み前提）
        T* Get() const;

        T* operator->() const { return Get(); }
        T& operator*()  const { return *Get(); }

        bool IsValid() const { return Get() != nullptr; }

        const std::string& GetId() const { return id_; }

    private:
        AssetManager* manager_ = nullptr; // 所有しない、ただのポインタ
        std::string   id_;
    };
}

