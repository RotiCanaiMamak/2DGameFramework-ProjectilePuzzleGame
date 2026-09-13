#pragma once
#include "SpriteBrush.h"
#include "FontBrush.h"
#include "GameStack.h"
#include "Level1.h"
#include "GameOver.h"
#include "Button.h"

class MainMenu : public GameScene
{
private:
	Audio& audio = Audio::getInstance();
	GameStack& gamestack = GameStack::getInstance();

public:
	void initialize() override;
	void update() override;

};

