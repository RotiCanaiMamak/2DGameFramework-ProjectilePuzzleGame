#pragma once
#include "DirectX.h"
#include "Line.h"

class LineBrush
{
private:
	LPD3DXLINE linebrush = NULL;

public:
	static LineBrush& getInstance() {
		static LineBrush instance;
		return instance;
	}
	void createline();
	void cleanline();
	void drawline(Line drawedline);
};
