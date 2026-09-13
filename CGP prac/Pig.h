#pragma once
#include "Sprite.h"
#include "GameObject.h"
#include "Texture.h"
#include <d3dx9.h>
#include <string>

using namespace std;

class Pig : public GameObject {
private:
    int type = 100;
    int hp = 100;
    bool dead = false;

public:
    Pig(int f, int g, int c, int r, int w, int h, int x, int y, const string& filename, D3DXVECTOR3 pos, D3DXCOLOR color, float mass, int t) :
        GameObject(f, g, c, r, w, h, x, y, filename, pos,color, mass),
        type(t)
    {
        if (type == 1) {
            hp = 100;
        }
        else if (type == 2) {
            hp = 300;
        }
        else if (type == 3) {
            hp = 500;
        }
    }

    Sprite& getSprite() {
        return sprite;
    }
    PhysicsManager& getPhysics() {
        return physics;
    }
    int getHP() {
        return hp;
    }
    bool getDead() {
        return dead;
    }

    float takeDamage(int dmg);

};

