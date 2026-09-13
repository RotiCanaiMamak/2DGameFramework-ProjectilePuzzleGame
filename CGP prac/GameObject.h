#pragma once
#include "SpriteBrush.h"
#include "Sprite.h"
#include "PhysicManager.h"
#include "Texture.h"
#include <d3dx9.h>
#include <string>

using namespace std;

class GameObject {
protected:
    Sprite sprite;
    PhysicsManager physics;

public:
    GameObject(int f, int g, int c, int r, int w, int h, int x, int y, const string& filename, D3DXVECTOR3 pos, D3DXCOLOR color, float mass = 1.0f) :
        sprite(f, g, c, r, w, h, x, y, filename, pos,color),
        physics(pos, mass)
    {
    }

    Sprite& getSprite() {
        return sprite;
    }

    PhysicsManager& getPhysics() {
        return physics;
    }

    virtual void updateSprite();

    virtual void updatePhysics();
};

