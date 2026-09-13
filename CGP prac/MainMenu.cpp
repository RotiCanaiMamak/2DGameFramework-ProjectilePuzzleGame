#include "MainMenu.h"

void MainMenu::initialize() {
	SpriteBrush& spritebrush = SpriteBrush::getInstance();
	Window& windows = Window::getInstance();

	audio.loadSounds("mainmenubgm", "assets\\Sounds\\Main Theme.wav", true);
	audio.playSound("mainmenubgm",1.0);

	//draw cursor
	initializeCursor();

	//background
	Texture bg("assets\\grassBg.jpg", D3DXVECTOR3(0, 0, 0), D3DCOLOR_XRGB(0, 0, 0), (FLOAT)windows.getwindowwidth() / 1024, (FLOAT)windows.getwindowheight() / 1024);
	textures.push_back(bg);

	//title
	D3DXVECTOR3 titlepos(890, 180, 0);
	Texture title("assets\\Title.png", titlepos, D3DCOLOR_XRGB(217, 217, 217),(float)0.8,(float)0.8);
	textures.push_back(title);
	
	// container
	RECT containerrect = { 680,150,1420,800 };
	Container maincontainer(containerrect, D3DCOLOR_XRGB(255, 255, 255));

	// Start button (moved up)
	D3DXVECTOR3 btnpos(800, 400, 0);
	//RECT btnrect = { 800,500,1131,564 };
	RECT btnrect = { 130,350,331,64 };
	//RECT txtrect = { 820,518,1121,554 };
	RECT txtrect = { 20,18,10,10 };

	Button startbtn(
		"assets\\mainmenubutton.png", btnpos, D3DCOLOR_XRGB(93, 93, 93),
		"Start Game", txtrect, D3DCOLOR_XRGB(0, 0, 0),
		btnrect, D3DCOLOR_XRGB(255, 255, 255),
		[&]() {
			audio.loadSounds("mainmenuui", "assets\\Sounds\\menu confirm.wav", false);
			audio.playSound("mainmenuui", 1.0);
			audio.stopsound("mainmenubgm");

			//audio.playSoundTouch();
			auto level1 = make_unique<Level1>();
			level1->initialize();	
			gamestack.pushscene(move(level1));
		}
	);

	//Sound button
	D3DXVECTOR3 btnpos2(800, 600, 0);
	RECT btnrect2 = { 130,500,331,64 };

	Button soundbtn(
		"assets\\mainmenubutton.png", btnpos2, D3DCOLOR_XRGB(93, 93, 93), audio.soundState, txtrect, D3DCOLOR_XRGB(0, 0, 0),
		btnrect2, D3DCOLOR_XRGB(255, 255, 255),
		[&]() {
			//audio.playSoundTouch();
			audio.toggleSound();

		}
	);

	// Volume Up Button and Down Button
	D3DXVECTOR3 posUp(800, 700, 0);
	RECT btnrectUp = { 130, 700, 331, 64};

	Button volUpBtn(
		"assets\\mainmenubutton.png", posUp, D3DCOLOR_XRGB(93, 93, 93),
		"Vol +",  txtrect, D3DCOLOR_XRGB(0, 0, 0),
		btnrectUp, D3DCOLOR_XRGB(255, 255, 255),
		[&]() {
			audio.increaseVolume();
			std::cout << "Volume: " << audio.masterVolume << std::endl;
		}
	);

	// Volume Down Button
	D3DXVECTOR3 posDown(800, 800, 0);
	RECT btnrectDown = { 130, 800, 331, 64 };

	Button volDownBtn(
		"assets\\mainmenubutton.png", posDown, D3DCOLOR_XRGB(93, 93, 93),
		"Vol -", txtrect, D3DCOLOR_XRGB(0, 0, 0),
		btnrectDown, D3DCOLOR_XRGB(255, 255, 255),
		[&]() {
			audio.decreaseVolume();
			std::cout << "Volume: " << audio.masterVolume << std::endl;
		}
	);


	maincontainer.addchild(startbtn);
	maincontainer.addchild(soundbtn);
	maincontainer.addchild(volDownBtn);
	maincontainer.addchild(volUpBtn);
	containers.push_back(maincontainer);
}
	
void MainMenu::update() {
	updateCursor();

	for (Container c : containers) {
		for (Button b : c.getchildren()) {
			//check mouse left click
			if (mousestate.rgbButtons[0] & 0x80) {
				if (b.onbutton(mouseposition.x, mouseposition.y)) {
					//audio.playSound("");
					b.click();
				}
			}
		}
	}
}