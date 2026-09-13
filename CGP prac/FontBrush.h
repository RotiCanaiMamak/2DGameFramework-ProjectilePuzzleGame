#pragma once
#include "DirectX.h"
#include "SpriteBrush.h"
#include "Font.h"
#include <map>
#include <utility>

using namespace std;

class FontBrush
{
private:
	LPD3DXFONT fontbrush;
	LPD3DXFONT newfontbrush;
	map<pair<int, int>, LPD3DXFONT> fontCache;
	SpriteBrush& spritebrush = SpriteBrush::getInstance();

public:
	static FontBrush& getInstance() {
		static FontBrush instance;
		return instance;
	}
	void createfont();
	void cleanfont();
	void drawfont(Font fontdrawed);
	LPD3DXFONT getfontbrush(Font fontdrawed);

};

