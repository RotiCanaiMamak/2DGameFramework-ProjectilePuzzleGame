#pragma once
#include <string>
#include <d3d9.h>
#include <d3dx9.h>
using namespace std;

class Font
{
private:
	string textoutput;
	RECT textrect;
	D3DCOLOR color;
	int textsize;
	int textwidth;

public:
	Font(){}

	Font(string t,RECT tr,D3DCOLOR c) {
		textoutput = t;
		textrect = tr;
		color = c;
		textsize = 45;
		textwidth = 0;
	}

	Font(string t, RECT tr, D3DCOLOR c,int ts, int tw) {
		textoutput = t;
		textrect = tr;
		color = c;
		textsize = ts;
		textwidth = tw;
	}

	string gettextoutput() {
		return textoutput;
	}

	RECT* gettextrectptr() {
		return &textrect;
	}
	RECT gettextrect() {
		return textrect;
	}
	D3DCOLOR getcolor() {
		return color;
	}
	int gettextsize() {
		return textsize;
	}
	int gettextwidth() {
		return textwidth;
	}

	void settextoutput(string txt) {
		textoutput = txt;
	}

	void settextrect(RECT r) {
		textrect = r;
	}
};

