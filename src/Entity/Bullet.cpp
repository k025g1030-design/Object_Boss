#include "Entity/Bullet.hpp"

namespace Entity {
    void Bullet::Update() {
        if (isAlive_) {
            position_ += vel_;
        }
        
    }
}
