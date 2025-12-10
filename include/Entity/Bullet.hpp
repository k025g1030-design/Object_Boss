#pragma once
#include"Core/Math.hpp"

namespace Entity {
    class Bullet {
    public:

        void Update();
        void SetVel(Core::Vector2 vel) {
            vel_ = vel;
        }
        Core::Vector2 GetVel() {
            return vel_;
        }

        void SetPosition(Core::Vector2 position) {
            position_ = position;
        }

        Core::Vector2 GetPosition() {
            return position_;
        }

        void SetKey(std::string key) {
            key_ = key;
        }

        std::string GetKey() {
            return key_;
        }

        void SetAlive(bool isAlive) {
            isAlive_ = isAlive;
        }

        bool IsAlive() {
            return isAlive_ && !key_.empty();
        }

        int GetAttack() {
            return attack_;
        }

        void SetAttack(int attack) {
            attack_ = attack;
        }
        void RefreshCoolDown() {
            if (isAlive_){
                coolDownTime_ -= 0.1f;
                if (coolDownTime_ < 0) {
                    coolDownTime_ = 10.f;
                    isAlive_ = false;
                    key_ = "";
                }
            }
        }
        void ResetCoolDown() {
            coolDownTime_ = 10.f;
        }
        float GetCoolDown() {
            return coolDownTime_;
        }
        

    private:
        Core::Vector2 position_;
        Core::Vector2 vel_;      // 速度
        std::string key_ = "";
        bool isAlive_ = false;
        float coolDownTime_ = 10.f;
        int attack_ = 10;
    };
}
