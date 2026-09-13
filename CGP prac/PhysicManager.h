#pragma once
#include <d3dx9.h>

class PhysicsManager {
private:
    D3DXVECTOR3 vector;
    D3DXVECTOR2 pos;
    D3DXVECTOR2 velocity;
    D3DXVECTOR2 acceleration;
    D3DXVECTOR2 center;
    float mass;
    float angle;

    static const D3DXVECTOR2 GRAVITY;
    static const float RESTITUTION;
    static const float FRICTION;

public:
    PhysicsManager(D3DXVECTOR3 startPos, float m) :
        vector(startPos),
        pos(startPos.x, startPos.y),
        velocity(0, 0),
        acceleration(0, 0),
        center(16, 16),
        mass(m),
        angle(0)
    {
    }

    D3DXVECTOR3 getVector() {
        return vector;
    }
    D3DXVECTOR2 getPosition() {
        return pos;
    }
    D3DXVECTOR2 getVelocity() {
        return velocity;
    }
    float getAngle() {
        return angle;
    }
    void setAngle(float ang) {
        angle = ang;
    }

    void launch(float force);
    void update();
    float wallCollision(float screenWidth, float screenHeight, float swidth);
    bool collisionWith(float thiswidth, float otherwidth, PhysicsManager& other, float& damageThis, float& damageOther);
    void boost(float force);
};
