#pragma once
#include "Sprite.h"
#include "GameObject.h"
#include "Texture.h"
#include <d3dx9.h>
#include <string>

using namespace std;

class Bird : public GameObject {
private:
    int type;
    bool boosted = false;
    bool launched = false;

public:
    Bird(int f, int g, int c, int r, int w, int h, int x, int y, const string& filename, D3DXVECTOR3 pos, D3DXCOLOR color, float mass, int t) :
        GameObject(f, g, c, r, w, h, x, y, filename, pos, color, mass),
        type(t)
    {
    }

    Sprite& getSprite() {
        return sprite;
    }
    PhysicsManager& getPhysics() {
        return physics;
    }
    bool getLaunched() {
        return launched;
    }
    //test only
    void launchTrue() {
        launched = true;
    }
    bool getBoost() {
        return boosted;
    }


    void updatePhysics() override;
    void boost(float force);
    void launch(float force);
};

