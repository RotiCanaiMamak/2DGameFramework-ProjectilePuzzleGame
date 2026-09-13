#pragma once
#include "UI.h"
#include "Texture.h"
#include "Font.h"
#include <string>
#include <functional>

using namespace std;

class Button : public UI
{

private:
	Texture btntexture;
	Font btnlabel;
	function<void()> onclick;
	
public:
	Button (){}

	Button(const string& filename, D3DXVECTOR3 p, D3DCOLOR xrgbcolor, string text, RECT tr, D3DCOLOR c, RECT r, D3DCOLOR bgc, function<void()> f ) : UI (r,bgc), btntexture(filename,p,xrgbcolor), btnlabel(text,tr,c), onclick(f){}

	void click() { if (onclick) onclick(); }

	Texture getbtntexture() {
		return btntexture;
	}

	Font getbtnlabel() {
		return btnlabel;
	}

	RECT getrect() {
		return rect;
	}

	void setbtnrect(RECT r) {
		rect = r;
	}

	void setposition(int x,int y) {
		btntexture.setpositionx(x);
		btntexture.setpositiony(y);
	}

	RECT gettxtrect() {
		return btnlabel.gettextrect();
	}

	void setbtntextrect(RECT r) {
		btnlabel.settextrect(r);
	}

	bool onbutton(float x, float y);
	

};

