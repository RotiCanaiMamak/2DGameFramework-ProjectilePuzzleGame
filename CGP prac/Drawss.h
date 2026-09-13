#pragma once
#include <d3dx9.h>
#include <iostream>
using namespace std;

class Drawss
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
	int maxframe, currentframe;
	LPDIRECT3DTEXTURE9 texture;
public:
	IDirect3DDevice9* d3dDevice;

	Drawss() {
		frame = 0;
		gap = 0;
		col = 0;
		row = 0;
		swidth = 0;
		sheight = 0;
		startx = 0;
		starty = 0;
		maxframe = 0;
		currentframe = 0;
		LPDIRECT3DTEXTURE9 texture = NULL;
	}
	Drawss(int f, int g, int c, int r, int w, int h, int x, int y) {
		frame = f;
		gap = g;
		col = c;
		row = r;
		swidth = w;
		sheight = h;
		startx = x;
		starty = y;
		maxframe = col*row;

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

	RECT getrectbox() {
		int w = startx + (frame % col) * swidth;
		int x = starty + (frame / col) * sheight;
		int y = gap + w + swidth;
		int z = gap + x + sheight;
		//cout << "RECT: " << w << "," << x << "," << y << "," << z << " Frame: " << frame << endl;
		return { w,x,y,z };
	}

	RECT getverticalrect() {
		int w = startx;
		int x = starty + (frame % row) * sheight;
		int y = w + swidth;
		int z = x + sheight;
		//cout << "RECT: " << w << "," << x << "," << y << "," << z << " Frame: " << frame << endl;
		return { w,x,y,z };
	}

	//RECT getrectbox2() {
	//	//cout << "RECT: " << w << "," << x << "," << y << "," << z << " Frame: " << frame << endl;
	//	return { w,x,y,z };
	//}
	void loadtexture() {
		if (FAILED(D3DXCreateTextureFromFileEx(d3dDevice, "assets\\militia.png", D3DX_DEFAULT, D3DX_DEFAULT,
			D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
			D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(185, 93, 110),
			NULL, NULL, &texture))) {
			MessageBox(NULL, "No Militia!", "ERROR", MB_OK);
		}
	}

	void calculateframe(int globalframe,int delay) {
		cout << globalframe << endl;
		currentframe = (globalframe/delay) % maxframe;
	}
};

