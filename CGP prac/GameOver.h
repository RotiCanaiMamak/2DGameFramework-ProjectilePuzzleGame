#pragma once
#include "GameScene.h"
#include "GameStack.h"
#include "MainMenu.h"
#include "AudioManager.h"

class GameOver : public GameScene
{

public:
	void initialize() override;
	void update() override;
};

