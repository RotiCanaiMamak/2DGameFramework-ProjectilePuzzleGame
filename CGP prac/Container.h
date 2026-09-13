#pragma once
#include "UI.h"
#include "Button.h"
#include <vector>
using namespace std;

class Container : public UI
{

private:
	vector<Button> children;

public:
	Container(RECT r, D3DCOLOR bgc) : UI(r, bgc){}

	void addchild(Button b);

	vector<Button> getchildren() {
		return children;
	}
};

