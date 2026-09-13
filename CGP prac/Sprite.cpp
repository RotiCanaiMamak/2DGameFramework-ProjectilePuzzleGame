#include "Sprite.h"

RECT Sprite::getrectbox() {

	int w = startx + (frame % col) * swidth;
	int x = starty + (frame / col) * sheight;
	int y = gap + w + swidth;
	int z = gap + x + sheight;
	//cout << "RECT: " << w << "," << x << "," << y << "," << z << " Frame: " << frame << endl;
	return { w,x,y,z };

}

RECT Sprite::getverticalrect() {

	int w = startx;
	int x = starty + (frame % row) * sheight;
	int y = w + swidth;
	int z = x + sheight;
	//cout << "RECT: " << w << "," << x << "," << y << "," << z << " Frame: " << frame << endl;
	return { w,x,y,z };

}

void Sprite::calculateframe(int globalframe, int delay) {
	// previous don't have framestart and frame end 
	// frame = (globalframe / delay) % maxframe;
	if (frameend >= framestart) {
		int range = frameend - framestart + 1;
		frame = framestart + (globalframe / delay) % range;
	}

}

void Sprite::setTransformRotate(float angleRadians) {
	D3DXVECTOR2 center(position.x + swidth / 2.0f, position.y + sheight / 2.0f);

	D3DXMatrixTransformation2D(
		&transmatrix,
		NULL,
		0,
		NULL,
		&center,
		angleRadians,
		NULL
	);
}

void Sprite::setframerange(int start, int end) {
	framestart = start;
	frameend = end;
}