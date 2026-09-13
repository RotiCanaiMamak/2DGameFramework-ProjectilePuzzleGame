#include "LevelCompleted.h"

void LevelCompleted::initialize() {
	Audio& audio = Audio::getInstance();
	GameStack& gamestack = GameStack::getInstance();
	SpriteBrush& spritebrush = SpriteBrush::getInstance();
	Window& windows = Window::getInstance();

	setbgred(211);
	setbggreen(175);
	setbgblue(55);

	audio.loadSounds("lvcpbgm", "assets\\Sounds\\Level Complete.wav", true);
	audio.playSound("lvcpbgm", 1.0);
	audio.loadSounds("lvcpbgm", "assets\\Sound\\slevel clear military a1.wav", true);
	audio.playSound("lvcpbgm", 1.0);

	//cursor
	initializeCursor();

	//background
	D3DXVECTOR3 bgpos(890, 0, 0);
	Texture gobg("assets\\gobackground.png", bgpos, D3DCOLOR_XRGB(255, 0, 0), 0.5f, 0.5f);
	textures.push_back(gobg);

	//levelcompleted text
	RECT textRect = { 790, 150, 1500, 500 };
	Font lvlcpt("Level Completed!", textRect, D3DCOLOR_XRGB(0, 0, 0), 72, 5);
	fonts.push_back(lvlcpt);

	//congratulation text
	textRect = { 790, 50, 2000, 200 };
	Font congratulationtxt("Congratulation!", textRect, D3DCOLOR_XRGB(255, 10, 10), 72, 5);
	fonts.push_back(congratulationtxt);

	//button
	RECT containerrect = { 680,150,1420,800 };
	Container gocontainer(containerrect, D3DCOLOR_XRGB(255, 255, 255));

	D3DXVECTOR3 btnpos(800, 350, 0);
	//RECT btnrect = { 800,350,1131,464 };
	RECT btnrect = { 150,200,331,114 };
	//RECT txtrect = { 820,368,1121,454 };
	RECT txtrect = { 20,18,10,10 };
	Button nextlvbtn("assets\\mainmenubutton.png", btnpos, D3DCOLOR_XRGB(93, 93, 93), "Next Level", txtrect, D3DCOLOR_XRGB(0, 0, 0), btnrect, D3DCOLOR_XRGB(255, 255, 255),
		[&]() {
			audio.stopallsound();
			auto leve2 = make_unique<Level2>();
			leve2->initialize();
			gamestack.pushscene(move(leve2));
		}
	);

	D3DXVECTOR3 mmbtnpos(800, 500, 0);
	//btnrect = { 800,500,1131,564 };
	btnrect = { 150,450,331,114 };
	//txtrect = { 820,518,1121,554 };
	txtrect = { 20,18,10,10 };
	Button mmbtn("assets\\mainmenubutton.png", mmbtnpos, D3DCOLOR_XRGB(93, 93, 93), "Main Menu", txtrect, D3DCOLOR_XRGB(0, 0, 0), btnrect, D3DCOLOR_XRGB(255, 255, 255),
		[&]() {
			audio.stopallsound();
			auto mainmenu = make_unique<MainMenu>();
			mainmenu->initialize();
			gamestack.pushscene(move(mainmenu));
		}
	);

	gocontainer.addchild(nextlvbtn);
	gocontainer.addchild(mmbtn);
	containers.push_back(gocontainer);
}

void LevelCompleted::update() {

	updateCursor();

	for (Container c : containers) {
		for (Button b : c.getchildren()) {
			//check mouse left click
			if (mousestate.rgbButtons[0] & 0x80) {
				if (b.onbutton(mouseposition.x, mouseposition.y)) {
					b.click();
				}
			}
		}
	}

}