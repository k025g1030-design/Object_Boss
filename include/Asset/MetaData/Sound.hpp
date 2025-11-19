#pragma once
#include <string>

/**

**/
namespace Asset {
    class Sound {
    public:
        explicit Sound() = default;
        explicit Sound(int handle, std::string path) : handle_(handle), path_(path) {}
        ~Sound() = default;

        int GetHandle() const {
            return handle_;
        }
        void SetHandle(int handle) {
            handle_ = handle;
        }
        std::string GetPath() const {
            return path_;
        }
        void SetPath(const std::string& path) {
            path_ = path;
        }

    private:
        int handle_{ -1 };
        std::string path_{ "" };
    };

}

