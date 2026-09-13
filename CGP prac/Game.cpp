#include "Game.h"
#include "LevelCompleted.h"

void Game::rungame(HINSTANCE hInstance) {
	Window& windows = Window::getInstance();

	windows.createwindow();

	HWND hwnd = windows.getg_hwnd();
	if (!IsWindow(hwnd)) {
		MessageBox(NULL, "HWND is invalid!", "Error", MB_OK);
	}

	DirectX& dx = DirectX::getInstance();

	if (dx.createdx()) {
		return;
	}

	SpriteBrush& spritebrush = SpriteBrush::getInstance();
	spritebrush.createsb();

	FontBrush& font = FontBrush::getInstance();
	font.createfont();

	LineBrush& line = LineBrush::getInstance();
	line.createline();
	
	DirectInput& directinput = DirectInput::getInstance();
	directinput.createdi();

	timer& frametimer = timer::getInstance();
	frametimer.Init(180);

	Audio& audio = Audio::getInstance();
	audio.initializeAudio();

	GameStack& gamestack = GameStack::getInstance();
	auto mainmenu = make_unique<MainMenu>();
	mainmenu->initialize();

	gamestack.pushscene(move(mainmenu));

	while (windows.runningwindow()) {
		//getinput
		gamestack.topscene()->input();

		//update
		int frame2update = frametimer.FramesToUpdate();
		for (int i = 0; i < frame2update; i++) {
			gamestack.topscene()->update();
		}

		//render
		gamestack.topscene()->render();

		//sound
		audio.updateSound();

	}

	directinput.cleandi();
	
	line.cleanline();

	font.cleanfont();

	spritebrush.cleansb();

	dx.cleandx();

	windows.closewindow(hInstance);

}