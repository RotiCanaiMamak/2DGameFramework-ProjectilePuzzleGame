#include "GameScene.h"

POINT GameScene::mouseposition = { 0, 0 };

void GameScene::initializeCursor() {
	SpriteBrush& spritebrush = SpriteBrush::getInstance();

	Texture cursor("assets\\newpointer.png", D3DXVECTOR3((float)mouseposition.x, (float)mouseposition.y, 0), D3DCOLOR_XRGB(0, 0, 0));

	//make cursor to be the first texture everytime
	textures.insert(textures.begin(), cursor);
}

void GameScene::updateCursor() {
	Window& windows = Window::getInstance();

	mouseposition.x += mousestate.lX;
	mouseposition.y += mousestate.lY;

	textures[0].setpositionx(mouseposition.x);
	textures[0].setpositiony(mouseposition.y);

	//let cursor inside the window
	if (mouseposition.x < 0)
		mouseposition.x = 0;
	else if (mouseposition.x > windows.getwindowwidth())
		mouseposition.x = windows.getwindowwidth();

	if (mouseposition.y < 0)
		mouseposition.y = 0;
	else if (mouseposition.y > windows.getwindowheight())
		mouseposition.y = windows.getwindowheight();
}

void GameScene::input() {
	DirectInput& directinput = DirectInput::getInstance();

	if (directinput.getkeyboard() == nullptr) {
		MessageBox(NULL, "Keyboard is NULL!", "Error", MB_OK);
	}
	//	Acquire the device.
	directinput.getkeyboard()->Acquire();
	directinput.getmouse()->Acquire();
	//	Get immediate Keyboard Data.
	directinput.getkeyboard()->GetDeviceState(256, dikeys);
	directinput.getmouse()->GetDeviceState(sizeof(DIMOUSESTATE), &mousestate);

}

void GameScene::render() {
	DirectX& directx = DirectX::getInstance();
	SpriteBrush& spritebrush = SpriteBrush::getInstance();
	FontBrush& fontbrush = FontBrush::getInstance();
	LineBrush& linebrush = LineBrush::getInstance();

	//	Clear the back buffer.
	directx.getdevice()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(bgred, bggreen, bgblue), 1.0f, 0);

	//	Begin the scene
	directx.getdevice()->BeginScene();

	//	Specify alpha blend will ensure that the sprite will render the background with alpha.
	spritebrush.getspritebrush()->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMATRIX oldmat;
	spritebrush.getspritebrush()->GetTransform(&oldmat);
	
	//draw all the sprite in vector<Sprite>
	for (Sprite s : sprites) {
		spritebrush.settranform(s.gettransmatrixptr());

		spritebrush.drawsprite(s);
	}

	//Draw Game Object
	for (GameObject* obj : gameObjects) {
		Sprite& s = obj->getSprite();  //get reference, not copy

		spritebrush.settranform(s.gettransmatrixptr());

		spritebrush.drawsprite(s);

	}

	//draw all the texture in vector<Texture>
	for (Texture t : textures) {
		spritebrush.settranform(t.gettransmatrixptr());

		spritebrush.drawtexture(t.gettexture(), t.getposition());
	}

	spritebrush.settranform(&oldmat);

	//draw all the font in vector<Font>
	for (Font f : fonts) {
		fontbrush.drawfont(f);
	}

	//draw all the line in vector<Line>
	for (Line l : lines) {
		linebrush.drawline(l);
	}

	//draw all ui
	for (Container c : containers) {
		for (Button b : c.getchildren()) {
			spritebrush.drawtexture(b.getbtntexture().gettexture(), b.getbtntexture().getposition());
			fontbrush.drawfont(b.getbtnlabel());
		}
	}

	//draw the cursor lastly to makesure cursor always on top level
	spritebrush.drawtexture(textures[0].gettexture(), textures[0].getposition());

	//	End sprite drawing
	spritebrush.getspritebrush()->End();

	//	End the scene
	directx.getdevice()->EndScene();

	//	Present the back buffer to screen
	directx.getdevice()->Present(NULL, NULL, NULL, NULL);

}

