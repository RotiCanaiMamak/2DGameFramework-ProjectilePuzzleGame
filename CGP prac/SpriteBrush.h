#pragma once
#include <d3dx9.h>
#include <string>
#include <iostream>
#include "DirectX.h"
class Sprite;

using namespace std;

class SpriteBrush
{
private:
	LPD3DXSPRITE spritebrush = NULL;
	LPDIRECT3DTEXTURE9 texture = nullptr;

public:
	static SpriteBrush& getInstance() {
		static SpriteBrush instance;
		return instance;
	}
	void createsb();
	void cleansb();
	LPDIRECT3DTEXTURE9 LoadTexture(const string& filename, D3DCOLOR colorkey);
	LPD3DXSPRITE getspritebrush() {
		return spritebrush;
	}
	void drawsprite(Sprite spritedrawed);
	void settranform(D3DXMATRIX* transformatrix);
	void drawtexture(LPDIRECT3DTEXTURE9 txture, D3DXVECTOR3& pos);
};

