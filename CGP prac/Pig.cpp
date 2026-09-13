#include "Pig.h"

float Pig::takeDamage(int dmg) {
    hp -= dmg;

    if (hp < 0) {
        hp = 0;
        dead = true;
    }

    if (hp <= 40) {
        sprite.setframerange(2, 3);
    }
    else if (hp <= 20) {
        sprite.setframerange(4, 5);
    }
    else {
        sprite.setframerange(0, 1);
    }

    return dmg;
}