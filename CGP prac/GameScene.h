#pragma once
#include "DirectInput.h"
#include "Sprite.h"
#include "Font.h"
#include "SpriteBrush.h"
#include "FontBrush.h"
#include "LineBrush.h"
#include "Container.h"
#include "GameObject.h" 
#include "Line.h" 
#include <vector>

using namespace std;

class GameScene
{

protected:
	BYTE  dikeys[256];
	DIMOUSESTATE mousestate;
	static POINT mouseposition;

	int bgred = 255;
	int bgblue = 255;
	int bggreen = 255;

	vector<Sprite> sprites;
	vector<Texture> textures;
	vector<Font> fonts;
	vector<Container> containers;
	vector<GameObject*> gameObjects;
	vector<Line> lines;
	
	void initializeCursor();
	void updateCursor();

public:
	virtual void initialize()=0;
	virtual void input();
	virtual void update()=0;
	virtual void render();

	void setbgred(int red) {
		bgred = red;
	}
	void setbggreen(int green) {
		bggreen = green;
	}
	void setbgblue(int blue) {
		bgblue = blue;
	}

	static void setMousePosition(POINT p) {
		mouseposition = p;
	}
	static POINT getMousePosition() {
		return mouseposition;
	}

};

