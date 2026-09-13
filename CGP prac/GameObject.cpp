#include "GameObject.h"

void GameObject::updatePhysics() {
    physics.update();

    D3DXVECTOR2 pos = physics.getPosition();
    sprite.setpositionx(pos.x);
    sprite.setpositiony(pos.y);

}

void GameObject::updateSprite() {
    sprite.setTransformRotate(physics.getAngle());
}