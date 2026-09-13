#pragma once
#include "DirectX.h"
#include "SpriteBrush.h"

using namespace std;

class Texture
{
private:
	LPDIRECT3DTEXTURE9 texture;
	D3DXVECTOR3 position;
	D3DXMATRIX transmatrix;

public:
	Texture(){}

	//default transformation matrix
	Texture(const string& filename, D3DXVECTOR3 pos, D3DCOLOR xrgbcolor) :
		position(pos)
	{
		SpriteBrush& spritebrush = SpriteBrush::getInstance();
		texture = spritebrush.LoadTexture(filename, xrgbcolor);
		D3DXMatrixIdentity(&transmatrix);
	}

	//transform (scale)
	Texture(const string& filename, D3DXVECTOR3 pos, D3DCOLOR xrgbcolor, float scaleX, float scaleY) :
		position(pos)
	{
		SpriteBrush& spritebrush = SpriteBrush::getInstance();
		texture = spritebrush.LoadTexture(filename, xrgbcolor);
		D3DXVECTOR2 scale(scaleX, scaleY);
		D3DXMatrixTransformation2D(&transmatrix, NULL, 0, &scale, NULL, 0, NULL);
	}

	LPDIRECT3DTEXTURE9* gettextureptr() {
		return &texture;
	}
	LPDIRECT3DTEXTURE9 gettexture() {
		return texture;
	}

	D3DXVECTOR3& getposition() {
		return position;
	}

	void setpositionx(float xp) {
		position.x = xp;
	}

	void setpositiony(float yp) {
		position.y = yp;
	}

	D3DXMATRIX gettransmatrix() {
		return transmatrix;
	}

	D3DXMATRIX* gettransmatrixptr() {
		return &transmatrix;
	}
};

