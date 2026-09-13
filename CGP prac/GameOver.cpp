#include "GameOver.h"

void GameOver::initialize() {
	Audio& audio = Audio::getInstance();
	GameStack& gamestack = GameStack::getInstance();
	SpriteBrush& spritebrush = SpriteBrush::getInstance();
	Window& windows = Window::getInstance();

	setbgred(94);
	setbggreen(94);
	setbgblue(94);

	audio.loadSounds("lvcpbgm", "assets\\Sounds\\level failed piglets a1.mp3", true);
	audio.playSound("lvcpbgm", 1.0);

	//cursor
	initializeCursor();

	//background
	D3DXVECTOR3 bgpos(890,0,0);
	Texture gobg("assets\\gobackground.png", bgpos, D3DCOLOR_XRGB(255, 0, 0),0.5f,0.5f);
	textures.push_back(gobg);

	//gameover pig
	D3DXVECTOR3 pigpos(700, 850, 0);
	Texture gopig("assets\\gopig.jpg", pigpos, D3DCOLOR_XRGB(0, 0, 0));
	textures.push_back(gopig);

	//game over text
	RECT textRect = { 820, 100, 1500, 500 };
	Font gameover("Game Over!", textRect, D3DCOLOR_XRGB(0, 0, 0),72,5);
	fonts.push_back(gameover);

	//pig dialog text
	textRect = { 1100, 850, 3000, 950 };
	Font pigdialog("Pig Laughing at u saying u are nub!", textRect, D3DCOLOR_XRGB(255, 10, 10), 32, 5);
	fonts.push_back(pigdialog);

	//button
	RECT containerrect = { 680,150,1420,800 };
	Container gocontainer(containerrect, D3DCOLOR_XRGB(255, 255, 255));

	D3DXVECTOR3 btnpos(800, 350, 0);
	//RECT btnrect = { 800,350,1131,464 };
	RECT btnrect = { 150,200,331,114};
	//RECT txtrect = { 820,368,1121,454 };
	RECT txtrect = { 20,18,10,10};
	Button restartbtn("assets\\mainmenubutton.png", btnpos, D3DCOLOR_XRGB(93, 93, 93),"Restart Game", txtrect, D3DCOLOR_XRGB(0, 0, 0), btnrect, D3DCOLOR_XRGB(255, 255, 255),
		[&]() {
			audio.stopsound("lvcpbgm");
			gamestack.popscene();
			gamestack.popscene();
		}
			);

	D3DXVECTOR3 mmbtnpos(800, 500, 0);
	//btnrect = { 800,500,1131,564 };
	btnrect = { 150,400,331,114};
	//txtrect = { 820,518,1121,554 };
	txtrect = { 20,18,10,10 };
	Button mmbtn("assets\\mainmenubutton.png", mmbtnpos, D3DCOLOR_XRGB(93, 93, 93),"Main Menu",txtrect, D3DCOLOR_XRGB(0, 0, 0), btnrect, D3DCOLOR_XRGB(255, 255, 255),
	[&]() {
			audio.stopallsound();
			auto mainmenu = make_unique<MainMenu>();
			mainmenu->initialize();
			gamestack.pushscene(move(mainmenu));
		}
		);

	gocontainer.addchild(restartbtn);
	gocontainer.addchild(mmbtn);
	containers.push_back(gocontainer);
}

void GameOver::update() {
	
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