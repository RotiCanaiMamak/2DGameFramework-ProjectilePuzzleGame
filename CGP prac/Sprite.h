#pragma once
#include "DirectX.h"
#include <string>
#include "SpriteBrush.h"

using namespace std;

class Sprite
{
private:
	int frame;
	int gap;
	int col;
	int row;
	int swidth;
	int sheight;
	int startx;
	int starty;
	int maxframe;
	int currentframe;
	int framestart;
	int frameend;
	LPDIRECT3DTEXTURE9 texture;
	D3DXVECTOR3 position;
	D3DXMATRIX transmatrix;

public:
	//default matrix
	Sprite(const string& filename, D3DXVECTOR3 pos, D3DCOLOR xrgbcolor) :
		position(pos),
		frame(0),
		gap(0),
		col(0),
		row(0),
		swidth(0),
		sheight(0),
		startx(0),
		starty(0),
		maxframe(0),  // col * row is 0 anyway
		currentframe(0)
	{
		SpriteBrush& spritebrush = SpriteBrush::getInstance();
		texture = spritebrush.LoadTexture(filename, xrgbcolor);
		D3DXMatrixIdentity(&transmatrix);
	}
	Sprite(LPDIRECT3DTEXTURE9 t, D3DXVECTOR3 p) :
		texture(t),
		position(p),
		frame(0),
		gap(0),
		col(0),
		row(0),
		swidth(0),
		sheight(0),
		startx(0),
		starty(0),
		maxframe(0),  // col * row is 0 anyway
		currentframe(0)
	{
		D3DXMatrixIdentity(&transmatrix);
	}


	//matrix
	Sprite(LPDIRECT3DTEXTURE9 t, D3DXVECTOR3 p, D3DXMATRIX m) :
		texture(t),
		position(p),
		transmatrix(m),
		frame(0),
		gap(0),
		col(0),
		row(0),
		swidth(0),
		sheight(0),
		startx(0),
		starty(0),
		maxframe(0),
		currentframe(0)
	{
	}

	//spritesheet
	Sprite(int f, int g, int c, int r, int w, int h, int x, int y, const string& filename, D3DXVECTOR3 p, D3DCOLOR xrgbcolor) :
		frame(f),
		gap(g),
		col(c),
		row(r),
		swidth(w),
		sheight(h),
		startx(x),
		starty(y),
		maxframe(c* r),
		currentframe(0),
		framestart(0),
		frameend(c* r - 1),
		position(p)
	{
		SpriteBrush& spritebrush = SpriteBrush::getInstance();
		texture = spritebrush.LoadTexture(filename, xrgbcolor);
		D3DXMatrixIdentity(&transmatrix);
	}
	Sprite(int f, int g, int c, int r, int w, int h, int x, int y, LPDIRECT3DTEXTURE9 t, D3DXVECTOR3 p) :
		frame(f),
		gap(g),
		col(c),
		row(r),
		swidth(w),
		sheight(h),
		startx(x),
		starty(y),
		maxframe(c* r),
		currentframe(0),
		texture(t),
		position(p)
	{
		D3DXMatrixIdentity(&transmatrix);  // optional if you want identity by default
	}

	int getframe() {
		return frame;
	}
	void setframe(int f) {
		frame = f;
	}
	int getcol() {
		return col;
	}
	int getrow() {
		return row;
	}
	int getwidth() {
		return swidth;
	}
	int getheight() {
		return sheight;
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

	void setMaxFrame(int maxframe) {
		this->maxframe = maxframe;
	}

	RECT getrectbox();

	RECT getverticalrect();

	void calculateframe(int globalframe, int delay);

	void setTransformRotate(float angleRadians);

	void setframerange(int start, int end);

};

