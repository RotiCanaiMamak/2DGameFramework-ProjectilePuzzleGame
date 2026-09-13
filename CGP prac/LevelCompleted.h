#pragma once
#include "GameScene.h"
#include "GameStack.h"
#include "MainMenu.h"
#include "Level2.h"
#include "timer.h"
#include "AudioManager.h"

class LevelCompleted : public GameScene
{

public:
	void initialize() override;
	void update() override;
};

