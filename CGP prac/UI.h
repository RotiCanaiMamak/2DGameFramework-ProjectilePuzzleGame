#pragma once
#include "DirectX.h"

class UI
{
protected:
	RECT rect;
	D3DCOLOR bgcolor;

public:
	UI() {
		ZeroMemory(&rect, sizeof(rect));
		bgcolor = D3DCOLOR_XRGB(255, 255, 255);
	}

	UI(RECT r, D3DCOLOR bgc) {	
		rect = r;
		bgcolor = bgc;
	}

	RECT getrect() {
		return rect;
	}

	D3DCOLOR getbgcolor() {
		return bgcolor;
	}

};

