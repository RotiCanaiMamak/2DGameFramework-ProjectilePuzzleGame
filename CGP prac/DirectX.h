#pragma once
#include <d3dx9.h>
#include "Window.h"

class DirectX
{

private:
	IDirect3DDevice9* d3dDevice;

public:
	static DirectX& getInstance() {
		static DirectX instance;
		return instance;
	}
	bool createdx();
	void cleandx();
	IDirect3DDevice9* getdevice() {
		return d3dDevice;
	}
};

