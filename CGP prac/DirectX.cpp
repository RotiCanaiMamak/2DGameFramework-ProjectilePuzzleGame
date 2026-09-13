#include "DirectX.h"

bool DirectX::createdx() {
	//get static window
	Window& windows = Window::getInstance();

	//	Define Direct3D 9.
	IDirect3D9* direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);//create object
	//same like this
	//int* x = new int(5);

	//	Define how the screen presents.
	D3DPRESENT_PARAMETERS d3dPP;
	ZeroMemory(&d3dPP, sizeof(d3dPP));

	//	Refer to Direct3D 9 documentation for the meaning of the members.
	d3dPP.Windowed = true;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = windows.getwindowwidth();
	d3dPP.BackBufferHeight = windows.getwindowheight();
	d3dPP.hDeviceWindow = windows.getg_hwnd();

	//	Create a Direct3D 9 device.
	HRESULT hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, windows.getg_hwnd(), D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);
	//like direct3D9.CreateDevice(...) then HRESULT hr will just reply success or fail,  so parameter &d3dDevice to tell createDevice and put at the table

	//	To Do: Cout out the message to indicate the failure.
	if (FAILED(hr))
		return false;	// or you can output a messagebox
}

void DirectX::cleandx() {
	//	Release the device when exiting.
	d3dDevice->Release();
	//	Reset pointer to NULL, a good practice.
	d3dDevice = NULL;
}