#include "Bird.h"

void Bird::updatePhysics() {
    if (launched) {
        physics.update();

        D3DXVECTOR2 pos = physics.getPosition();
        sprite.setpositionx(pos.x);
        sprite.setpositiony(pos.y);
    }
}

void Bird::launch(float force) {
    if (launched != true) {
        physics.launch(force);
        launched = true;
    }
}

void Bird::boost(float force) {
    if (type == 2 && !boosted) {
        physics.boost(force);
        boosted = true;
    }
}