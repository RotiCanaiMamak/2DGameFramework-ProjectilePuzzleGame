#pragma once
#include<d3dx9.h>

class Line
{
private:
	D3DXVECTOR2 vertices[2];
	D3DCOLOR linecolor;
	float width = 0;

public:
	Line(D3DXVECTOR2 start, D3DXVECTOR2 end, D3DCOLOR color,float w) {
		vertices[0] = start;
		vertices[1] = end;
		linecolor = color;
		width = w;
	}

	D3DXVECTOR2* getvertices() {
		return vertices;
	}

	D3DCOLOR getlinecolor() {
		return linecolor;
	}

	float getwidth() {
		return width;
	}
};

