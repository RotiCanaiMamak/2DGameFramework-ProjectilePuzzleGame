#include "PhysicManager.h"
#include <cmath>    

const D3DXVECTOR2 PhysicsManager::GRAVITY(0.0, 0.2);
const float PhysicsManager::RESTITUTION = 0.3;
const float PhysicsManager::FRICTION = 0.8;

void PhysicsManager::launch(float force) {
    acceleration += D3DXVECTOR2((force / mass) * cosf(angle), (force / mass) * sinf(angle));
}

void PhysicsManager::update() {
    acceleration += GRAVITY;

    velocity += acceleration;
    pos += velocity;
    vector.x = pos.x;
    vector.y = pos.y;

    acceleration = D3DXVECTOR2(0, 0);
}

float PhysicsManager::wallCollision(float screenWidth, float screenHeight, float swidth) {
    float damage = 0;

    //check floor first(avoid stuttering)
    if (pos.y + swidth >= screenHeight) {
        pos.y = screenHeight - swidth;
        D3DXVECTOR2 normal(0, -1);
        float dot = D3DXVec2Dot(&velocity, &normal);

        float j = -(1 + RESTITUTION) * dot * mass;
        D3DXVECTOR2 impulse = (j / mass) * normal;
        velocity += impulse;
        velocity.x *= FRICTION;

        //reduce very smol vel to reduce bug
        if (velocity.y < 0.2) {
            acceleration.y = 0;
        }

        D3DXVECTOR2 dvThis = impulse / mass;

        damage += D3DXVec2Length(&dvThis);
    }

    if (pos.x <= 0) {
        pos.x = 0;
        D3DXVECTOR2 normal(1, 0);
        float dot = D3DXVec2Dot(&velocity, &normal);
        float j = -(1 + RESTITUTION) * dot * mass;
        D3DXVECTOR2 impulse = (j / mass) * normal;
        velocity += impulse;

        D3DXVECTOR2 dvThis = impulse / mass;

        damage += D3DXVec2Length(&dvThis);
    }

    if (pos.x + swidth >= screenWidth) {
        pos.x = screenWidth - swidth;
        D3DXVECTOR2 normal(-1, 0);
        float dot = D3DXVec2Dot(&velocity, &normal);

        float j = -(1 + RESTITUTION) * dot * mass;
        D3DXVECTOR2 impulse = (j / mass) * normal;
        velocity += impulse;

        D3DXVECTOR2 dvThis = impulse / mass;

        damage += D3DXVec2Length(&dvThis);

    }

    if (pos.y <= 0) {
        pos.y = 0;
        D3DXVECTOR2 normal(0, 1);
        float dot = D3DXVec2Dot(&velocity, &normal);

        float j = -(1 + RESTITUTION) * dot * mass;
        D3DXVECTOR2 impulse = (j / mass) * normal;
        velocity += impulse;

        D3DXVECTOR2 dvThis = impulse / mass;

        damage += D3DXVec2Length(&dvThis);
    }

    return damage;
}

bool PhysicsManager::collisionWith(float thiswidth, float otherwidth, PhysicsManager& other, float& damageThis, float& damageOther) {
    D3DXVECTOR2 distance = pos - other.pos; //actual distance of the 2 object (when overlap)
    float distLen = D3DXVec2Length(&distance);
    float minDist = thiswidth / 2 + otherwidth / 2; //find the minimum distance of the 2 objects for no overlapping 

    if (distLen < minDist && distLen != 0) { //prevent divide by zero
        D3DXVECTOR2 normal;
        D3DXVec2Normalize(&normal, &distance); //collision normal 

        //push objects so they wont overlap
        float overlap = minDist - distLen;
        pos += normal * (overlap / 2); 
        other.pos -= normal * (overlap / 2);

        D3DXVECTOR2 relativeVelocity = other.velocity - velocity;
        float dot = D3DXVec2Dot(&relativeVelocity, &normal); //relative velocity along the normal

        /*HOW THE FORMULA WORKS
            Vrel = (v2 - v1) * n

            impulse = j * n

            During collision, impulse acts along the normal: 
            deltaV = impulse/m, v'-v = impulse/m, v' = v + impulse/m 
             (v1' = v1- impulse/m1 cause the impulse is opposite of the normal)

            plug in RESTITUTION: Vrel * RESTITUTION, (v2'-v1')*n = -(v2-v1)*n*RESTITUTION 
            for above: after collision, the relative velocity along the normal reverse direction and is scaled by RESTITUTION

            [(v2 + j/m1 * n)-(v1 - j/m2 * n)]*n = -(v2-v1)*RESTITUTION*n
            n(v2-v1) + j(1/m1 + 1/m2) = -(v2-v1)*RESTITUTION*n   
            j(1/m1 + 1/m2) = (v2-v1)(-RESTITUTION-1)
            j = -[(v2-v1)(RESTITUTION+1)] / (1/m1 + 1/m2)
        */

        float j = -(dot * (RESTITUTION + 1)) / ((1 / mass) + (1 / other.mass));

        D3DXVECTOR2 impulse = j * normal;
        velocity -= impulse / mass; // (v1' = v1 - impulse/m1 cause the impulse is opposite of the normal)
        other.velocity += impulse / other.mass; //v' = v + impulse/m

        D3DXVECTOR2 dvThis = impulse / mass;
        D3DXVECTOR2 dvOther = impulse / other.mass;

        damageThis = D3DXVec2Length(&dvThis);
        damageOther = D3DXVec2Length(&dvOther);

        return true;
    }
    return false;
}

void PhysicsManager::boost(float force) {
    acceleration += D3DXVECTOR2((force / mass) * cosf(angle), (force / mass) * sinf(angle));
}
