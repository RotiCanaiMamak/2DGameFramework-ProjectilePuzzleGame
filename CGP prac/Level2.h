#pragma once
#include "GameScene.h"
#include "Bird.h"
#include "Pig.h"
#include "Font.h"
#include <iostream>
#include "GameStack.h"
#include "GameOver.h"
#include "LevelCompleted.h"

class Level2 : public GameScene
{
private:
    int globalFrame;

    float powerMeter = 0;
    float powerMax = 200;
    float powerIncrement = 0.4;

    float walldamagescale = 4;
    float damagescale = 4;

    float boostForce = 50;

    bool charging = false;

    bool win = false;
    bool lose = false;

    int launchFrameCounter = 0;
    int launchDelayFrames = 240; //for bird spawning
    int winFrameCounter = 0;
    int loseFrameCounter = 0;
    int delayFrames = 720; //change if u wanna delay loonger

    int amountOfRed = 0;
    int amountOfChuck = 10;
    int amountOfTerence = 0;
    Bird* red = nullptr;
    Bird* chuck = nullptr;
    Bird* terrence = nullptr;
    vector<Bird*> birds;
    vector<Bird*> tests;
    vector<GameObject*> toDelete;
    int currentBirdIndex = 0;

    int score = 0;
    float centerx;
    float centery;
    float radius;

    GameStack& gamestack = GameStack::getInstance();
    Audio& audio = Audio::getInstance();

public:
    Level2() :
        globalFrame(0)
    {
    }

    int getscore() {
        return score;
    }


    void initialize() override;
    void update() override;
};