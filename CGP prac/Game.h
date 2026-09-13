#pragma once
#include "Window.h"
#include "timer.h"
#include "DirectX.h"
#include "SpriteBrush.h"
#include "FontBrush.h"
#include "LineBrush.h"
#include "DirectInput.h"
#include "GameStack.h"
#include "MainMenu.h"
#include "AudioManager.h"

class Game
{

public:
	static Game getInstance() {
		static Game instance;
		return instance;
	}
	void rungame(HINSTANCE hInstance);
};

