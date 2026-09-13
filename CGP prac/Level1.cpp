#include "Level1.h"
#include "Window.h"

using namespace std;

void Level1::initialize() {
    SpriteBrush& spritebrush = SpriteBrush::getInstance();
    Window& windows = Window::getInstance();

    audio.loadSounds("lv1a", "assets\\Sounds\\level start military a1.mp3", false);
    audio.playSound("lv1a", 1.0);
    audio.loadSounds("lv1bgm", "assets\\Sounds\\IntroCut.wav", true);
    audio.playSound("lv1bgm", 0.8);

    audio.loadSounds("flyingbird", "assets\\Sounds\\bird 01 flying.wav", false);
    audio.loadSounds("sltredbird", "assets\\Sounds\\bird 01 select.wav", false);
    audio.loadSounds("sltyellowbird", "assets\\Sounds\\bird 03 select.wav", false);
    audio.loadSounds("sltterence", "assets\\Sounds\\bird 01 select_low.wav", false);
    audio.loadSounds("birdstreched", "assets\\Sounds\\slingshot streched.wav", false);
    audio.loadSounds("woodcollision", "assets\\Sounds\\wood damage a2.wav", false);
    audio.loadSounds("pigcollision", "assets\\Sounds\\piglette collision a2.wav", false);
    audio.loadSounds("birdcollision", "assets\\Sounds\\bird 01 collision a4.wav", false);

    initializeCursor();

    for (int i = 0; i < amountOfRed; i++) {
        Bird* red = new Bird(
            0, 0,
            2, 1,
            85, 84,
            0, 0,
            "assets\\birds.png",
            D3DXVECTOR3(0, 500, 0),
            D3DCOLOR_XRGB(217, 217, 217),
            5, 1
        );
        birds.push_back(red);
    }

    for (int i = 0; i < amountOfChuck; i++) {
        chuck = new Bird(
            0, 0,
            3, 1,
            83, 88,
            258, 0,
            "assets\\birds.png",
            D3DXVECTOR3(0, 500, 0),
            D3DCOLOR_XRGB(217, 217, 217),
            5, 2
        );
        birds.push_back(chuck);
    }

    for (int i = 0; i < amountOfTerence; i++) {
        terrence = new Bird(
            0, 0,
            3, 1,
            85, 85,
            0, 174,
            "assets\\birds.png",
            D3DXVECTOR3(0, 500, 0),
            D3DCOLOR_XRGB(217, 217, 217),
            10, 3
        );
        birds.push_back(terrence);
    }

    test1 = new Bird(
        0, 0,
        2, 1,
        85, 84,
        0, 0,
        "assets\\birds.png",
        D3DXVECTOR3(0, 1000, 0),
        D3DCOLOR_XRGB(217, 217, 217),
        5, 1
    );
    tests.push_back(test1);

    test2 = new Bird(
        0, 0,
        3, 1,
        85, 85,
        0, 174,
        "assets\\birds.png",
        D3DXVECTOR3(100, 1000, 0),
        D3DCOLOR_XRGB(217, 217, 217),
        10, 3
    );
    tests.push_back(test2);
    test2->getPhysics().setAngle(D3DX_PI);
    test2->launchTrue();

    D3DXVECTOR3 ballspos[] = {
    D3DXVECTOR3(1600, 1000, 0),
    D3DXVECTOR3(1600, 800, 0),
    D3DXVECTOR3(1600, 600, 0),
    D3DXVECTOR3(1600, 400, 0),
    D3DXVECTOR3(1000, 1000, 0),
    D3DXVECTOR3(1000, 800, 0),
    D3DXVECTOR3(1000, 600, 0),
    D3DXVECTOR3(1000, 400, 0),
    D3DXVECTOR3(1300, 50, 0),
    };

    for (int i = 0; i < 9; i++) {
        GameObject* woodenBall = new GameObject(
            0, 0,
            1, 1,
            72, 72,
            90, 177,
            "assets\\SpriteSheet - Objects.png",
            ballspos[i],
            D3DCOLOR_XRGB(217, 217, 217),
            100
        );
        gameObjects.push_back(woodenBall);
    }

    D3DXVECTOR3 pigspos[] = {
    D3DXVECTOR3(1200, 1000, 0),
    D3DXVECTOR3(1200, 50, 0),
    D3DXVECTOR3(1400, 1000, 0),
    D3DXVECTOR3(1400, 50, 0),
    D3DXVECTOR3(1300, 1000, 0),
    D3DXVECTOR3(1600, 200, 0),
    D3DXVECTOR3(1000, 200, 0),
    };

    for (int i = 0; i < 7; i++) {
        Pig* pig = new Pig(
            0, 0,
            3, 2,
            80, 80,
            262, 172,
            "assets\\birds.png",
            pigspos[i],
            D3DCOLOR_XRGB(217, 217, 217),
            10, 1
        );
        gameObjects.push_back(pig);
        cout << pig->getHP();
    }

    //score
    RECT textRect = { 1580,100,1920,200 };
    string scorevalue = "Score: " + to_string(score);
    Font fontscore(scorevalue, textRect, D3DCOLOR_XRGB(10, 10, 10), 72, 10);
    fonts.push_back(fontscore);

    //power meter line start and end
    textRect = { 130,300,200,400 };
    Font start0("0", textRect, D3DCOLOR_XRGB(10, 10, 10), 26, 10);
    fonts.push_back(start0);

    textRect = { 450,300,550,400 };
    Font end100("100", textRect, D3DCOLOR_XRGB(10, 10, 10), 26, 10);
    fonts.push_back(end100);

    //power meter line
    centerx = 300;
    centery = 300;
    radius = 150;

    for (int i = 0; i <= 30; i++) {
        float theta1 = D3DX_PI - (i / 30.0f * D3DX_PI);
        float theta2 = D3DX_PI - ((i + 1) / 30.0f * D3DX_PI);
        D3DXVECTOR2 p1 = { centerx + cos(theta1) * radius, centery - sin(theta1) * radius };
        D3DXVECTOR2 p2 = { centerx + cos(theta2) * radius, centery - sin(theta2) * radius };

        Line linepowerMeter(p1, p2, D3DCOLOR_XRGB(0, 0, 0), 2.0f);
        lines.push_back(linepowerMeter);
    }

    D3DXVECTOR2 start = { centerx, centery };
    D3DXVECTOR2 end = { centerx - radius, centery };

    Line pointer(start, end, D3DCOLOR_XRGB(255, 0, 0), 2.0f);
    lines.push_back(pointer);

}

void Level1::update() {
    Window& windows = Window::getInstance();

    updateCursor();

    //for showing mass collision, test ony
    bool isLaunched = false;
    for (Bird* bird : tests) {
        if (find(gameObjects.begin(), gameObjects.end(), bird) == gameObjects.end()) {
            gameObjects.push_back(bird);
        }
        if (isLaunched == false) {
            if (dikeys[DIK_T] & 0x80) {
                bird->launch(100);
                isLaunched = true;
            }
        }
    }

    int prevIndex = currentBirdIndex; //(useless now)

    Bird* activeBird = birds[currentBirdIndex];

    //reset angle everytime it's called (useless now)
    if (prevIndex != currentBirdIndex && !activeBird->getLaunched()) {
        activeBird->getPhysics().setAngle(0);
    }
    //make unlaunched birds disappear (useless now)
    if (!birds[prevIndex]->getLaunched()) {
        gameObjects.erase(
            remove(gameObjects.begin(), gameObjects.end(), birds[prevIndex]),
            gameObjects.end()
        );
    }
    //show 1st bird
    if (find(gameObjects.begin(), gameObjects.end(), birds[currentBirdIndex]) == gameObjects.end()) {
        gameObjects.push_back(birds[currentBirdIndex]);
    }

    if (dikeys[DIK_SPACE] & 0x80 && !activeBird->getLaunched()) {
        if (!charging) {
            charging = true;
            audio.playSound("birdstreched", 1.0);
        }
    }
    else {
        if (charging) {
            activeBird->launch(powerMeter);
            charging = false;
            powerMeter = 0;
            audio.playSound("flyingbird", 1.0);
        }
    }
    if (charging) {
        if (powerMeter < powerMax) {
            powerMeter += powerIncrement;
            if (powerMeter > powerMax) {
                powerMeter = powerMax;
            }
        }
    }

    // change to the next bird automatically
    if (activeBird->getLaunched()) {
        launchFrameCounter++;

        if (launchFrameCounter >= launchDelayFrames) {

            for (int i = 0; i < birds.size(); i++) {
                if (!birds[i]->getLaunched()) {
                    currentBirdIndex = i;
                    break;
                }
            }

            activeBird = birds[currentBirdIndex];

            if (find(gameObjects.begin(), gameObjects.end(), activeBird) == gameObjects.end()) { // check if already in game object vector
                gameObjects.push_back(activeBird);
            }

            launchFrameCounter = 0;
        }
    }

    if (!activeBird->getLaunched()) {
        if (dikeys[DIK_LEFT] & 0x80) {
            activeBird->getPhysics().setAngle(activeBird->getPhysics().getAngle() - 0.05);
        }
        else if (dikeys[DIK_RIGHT] & 0x80) {
            activeBird->getPhysics().setAngle(activeBird->getPhysics().getAngle() + 0.05);
        }
    }

    //collision
    for (int i = 0; i < gameObjects.size(); i++) {
        for (int j = i + 1; j < gameObjects.size(); j++) {
            GameObject* obj1 = gameObjects[i];
            GameObject* obj2 = gameObjects[j];

            float damage1 = 0;
            float damage2 = 0;

            if (obj1->getPhysics().collisionWith(
                (FLOAT)obj1->getSprite().getwidth(),
                (FLOAT)obj2->getSprite().getwidth(),
                obj2->getPhysics(),
                damage1, damage2)) {

                Pig* pig1 = dynamic_cast<Pig*>(obj1);
                Pig* pig2 = dynamic_cast<Pig*>(obj2);
                Bird* bird1 = dynamic_cast<Bird*>(obj1);
                Bird* bird2 = dynamic_cast<Bird*>(obj2);

                if (damage1 * damagescale > 5) {

                    if (obj1 == bird1) {
                        audio.playSound("birdcollision", 1.0);

                    }
                    if (obj1 == pig1) {
                        cout << "\nCollision1: " << pig1->takeDamage((int)(damage1 * damagescale));
                        cout << "\n HP1: " << pig1->getHP();
                        audio.playSound("pigcollision", 1.0);

                        if (pig1->getHP() <= 0) {
                            if (find(toDelete.begin(), toDelete.end(), pig1) == toDelete.end()) {
                                toDelete.push_back(pig1);
                                score += 100;
                            }
                        }
                    }
                }
                if (damage2 * damagescale > 5) {

                    if (obj2 == bird2) {
                        audio.playSound("birdcollision", 1.0);

                    }
                    if (obj2 == pig2) {
                        audio.playSound("pigcollision", 1.0);
                        cout << "\nCollision2: " << pig2->takeDamage((int)(damage2 * damagescale));
                        cout << "\n HP2: " << pig2->getHP();
                        if (pig2->getHP() <= 0) {
                            if (find(toDelete.begin(), toDelete.end(), pig2) == toDelete.end()) {
                                toDelete.push_back(pig2);
                                score += 100;
                            }
                        }
                    }
                }

            }
        }
    }

    for (GameObject* obj : gameObjects) {
        Bird* bird = dynamic_cast<Bird*>(obj);
        if (bird != NULL && bird == activeBird) {
            if (bird->getLaunched()) {
                if (dikeys[DIK_SPACE] & 0x80) {
                    activeBird->boost(boostForce);
                }
            }
        }

        float damage = obj->getPhysics().wallCollision(
            (FLOAT)windows.getwindowwidth(),
            (FLOAT)windows.getwindowheight(),
            obj->getSprite().getheight()
        );


        if (damage * walldamagescale > 5) {
            if (obj == bird) {
                audio.playSound("birdcollision", 1.0);

            }
            Pig* pig = dynamic_cast<Pig*>(obj);
            if (pig) {
                cout << "\nWall: Pig took " << pig->takeDamage((int)(damage * walldamagescale));
                cout << "\n HP: " << pig->getHP();
                audio.playSound("woodcollision", 1.0);
                if (pig->getHP() <= 0) {
                    if (find(toDelete.begin(), toDelete.end(), pig) == toDelete.end()) {
                        toDelete.push_back(pig);
                        score += 100;
                    }
                }
            }
        }

        obj->updateSprite();
        obj->updatePhysics();

        obj->getSprite().calculateframe(globalFrame, 30);
    }

    //delete objects in toDelete
    for (GameObject* obj : toDelete) {
        gameObjects.erase(remove(gameObjects.begin(), gameObjects.end(), obj), gameObjects.end());
        delete obj;
    }
    toDelete.clear(); //clear all toDelete objects for next loop

    globalFrame++;

    //update the score
    fonts[0].settextoutput("Score: " + std::to_string(score));

    win = true;
    for (GameObject* obj : gameObjects) {
        if (dynamic_cast<Pig*>(obj)) {
            win = false;
            winFrameCounter = 0;
            break;
        }
    }
    lose = true;
    for (GameObject* obj : gameObjects) {
        Bird* bird = dynamic_cast<Bird*>(obj);
        if (bird && !bird->getLaunched()) {
            lose = false;
            loseFrameCounter = 0;
            break;
        }
    }

    if (dikeys[DIK_N] & 0x80) {
        audio.stopallsound();
        auto lvlc = make_unique<LevelCompleted>();
        lvlc->initialize();
        gamestack.pushscene(move(lvlc));
    }

    if (win) {
        winFrameCounter++;
        if (winFrameCounter >= delayFrames) {
            audio.stopallsound();
            auto lvlc = make_unique<LevelCompleted>();
            lvlc->initialize();
            gamestack.pushscene(move(lvlc));
        }
    }

    if (birds.empty() && win == false) {
        lose = true;
    }
    if (lose) {
        loseFrameCounter++;
        if (loseFrameCounter >= delayFrames) {
            audio.stopallsound();
            auto go = make_unique<GameOver>();
            go->initialize();
            gamestack.pushscene(move(go));
        }
    }

    //update the line
    float ratio = powerMeter / powerMax;
    float angle = D3DX_PI - (ratio * D3DX_PI);

    float endx = centerx + cos(angle) * radius;
    float endy = centery - sin(angle) * radius;

    Line pointer({ centerx,centery }, { endx, endy }, D3DCOLOR_XRGB(255, 0, 0), 2.0f);
    lines.back() = pointer;
}
