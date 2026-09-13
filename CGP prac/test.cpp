//Ask the compiler to include minimal header files for our program.
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
//include the Direct3D 9 library
#include <d3d9.h>
#include <d3dx9.h>

//	Ask the compiler to include minimal header files for our program.
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
//	include the Direct3D 9 library
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <iostream>
#include <string>
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
//--------------------------------------------------------------------
using namespace std;

//DirectX globals
LPDIRECTINPUT8 dInput;
LPDIRECTINPUTDEVICE8  dInputKeyboardDevice;
LPD3DXFONT font = NULL;

//DirectX mouse
LPDIRECTINPUT8 dInput2;
LPDIRECTINPUTDEVICE8  dInputMouseDevice;
DIMOUSESTATE mousestate;
LONG xPos = 0;
LONG yPos = 0;
string textx = "";
string texty = "";
string vectortext;
char vectorchar[999];

//Define Direct3D 9
LPDIRECT3DTEXTURE9 cursorTexture = NULL;
D3DXVECTOR3 cursorPosition;
LPDIRECT3DTEXTURE9 texture1 = NULL;
LPDIRECT3DTEXTURE9 texture2 = NULL;
LPDIRECT3DTEXTURE9 texture3 = NULL;
LPDIRECT3DTEXTURE9* texturenum = &texture1;
D3DXVECTOR3 vector1 = D3DXVECTOR3(1024, 0, 0);
D3DXVECTOR3 vector2 = D3DXVECTOR3(1024, 64, 0);
D3DXVECTOR3 vector3 = D3DXVECTOR3(1024, 128, 0);
LPDIRECT3DTEXTURE9 test1 = NULL;
LPDIRECT3DTEXTURE9 pic1 = NULL;
LPDIRECT3DTEXTURE9 pic2 = NULL;
LPDIRECT3DTEXTURE9 bgTextures[3] = { NULL, NULL, NULL };
int currentBgIndex = 0;
LPDIRECT3DTEXTURE9 numberTexture = NULL;
int digitColumn = 0;
int digitRow = 0;
int piccol = 0, picrow = 0;
int picmaxcol = 2, picmaxrow = 2;
int numcol = 0, numrow = 0;
int nummaxcol = 4, nummaxrow = 4;
int testcol = 0, testrow = 0;
int testmaxcol = 3, testmaxrow = 4;
bool colourasc1 = true;
bool colourasc2 = true;
bool colourasc3 = true;
int colournum1 = 0;
int colournum2 = 0;
int colournum3 = 0;
int colourinc1 = 5;
int colourinc2 = 5;
int colourinc3 = 5;


//FontBrush
LPD3DXFONT fontBrush = NULL;
RECT textRect = { 100, 100, 300, 150 };

IDirect3DDevice9* d3dDevice;
//--------------------------------------------------------------------
WNDCLASS wndClass;
MSG msg;

//	Window handle
HWND g_hWnd = NULL;
LPD3DXSPRITE spritebrush = NULL;
IDirect3D9* direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);
D3DPRESENT_PARAMETERS d3dPP;
POINT mousePos;
HRESULT hr;
//--------------------------------------------------------------------

//Color setting
int color, red = 0, green = 0, blue = 0;
bool colorflag, redflag = true, blueflag = true, greenflag = true;

void ir(int& color, bool& colorflag) {
	color += 5;
	if (color > 254) {
		colorflag = false;
	}
}

void dr(int& color, bool& colorflag) {
	color -= 5;
	if (color < 1) {
		colorflag = true;
	}
}

//Movement
POINT position = { 100, 100 };
const int movementSpeed = 5;


void fs(HWND hWnd)
{
	static bool isFullscreen = false;
	static WINDOWPLACEMENT wp = { sizeof(wp) };

	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);

	if (!isFullscreen)
	{
		GetWindowPlacement(hWnd, &wp);

		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);

		MONITORINFO mi = { sizeof(mi) };
		if (GetMonitorInfo(MonitorFromWindow(hWnd, MONITOR_DEFAULTTOPRIMARY), &mi))
		{
			SetWindowPos(hWnd, HWND_TOP,
				mi.rcMonitor.left, mi.rcMonitor.top,
				mi.rcMonitor.right - mi.rcMonitor.left,
				mi.rcMonitor.bottom - mi.rcMonitor.top,
				SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
		}

		isFullscreen = true;
	}
	else
	{
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(hWnd, &wp);
		SetWindowPos(hWnd, NULL, 0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
			SWP_NOOWNERZORDER | SWP_FRAMECHANGED);

		isFullscreen = false;
	}
}

//	Window Procedure, for event handling
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//	The message is post when we destroy the window.
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

		/*case VK_ESCAPE:
			PostQuitMessage(0);
			break;*/
	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		case 'R':
			if (redflag) {
				ir(red, redflag);
			}
			else {
				dr(red, redflag);
			}
			break;
		case 'B':
			if (blueflag) {
				ir(blue, blueflag);
			}
			else {
				dr(blue, blueflag);
			}
			break;
		case 'G':
			if (greenflag) {
				ir(green, greenflag);
			}
			else {
				dr(green, greenflag);
			}
			break;
		case 'F':
			fs(hWnd);
			break;

		case 'A': // Move to previous background
			currentBgIndex--;
			if (currentBgIndex < 0)
			{
				currentBgIndex = 2;
			}
			break;
		case 'D': // Move to next backgraound
			currentBgIndex++;
			if (currentBgIndex > 2)
			{
				currentBgIndex = 0;
			}
			break;

		case 'J': // Previous digit
			digitColumn--;
			if (digitColumn < 0)
			{
				digitColumn = 3;
			}
			break;
		case 'L': // Next digit
			digitColumn++;
			if (digitColumn > 3)
			{
				digitColumn = 0;
			}
			break;

		case 'K': // Go to the bottom of the digit
			digitRow++;
			if (digitRow > 3)
			{
				digitRow = 0;
			}
			break;
		case 'I': // Go to the top of the digit
			digitRow--;
			if (digitRow < 0)
			{
				digitRow = 3;
			}
			break;

		case VK_LEFT:
			position.x -= movementSpeed;
			break;
		case VK_RIGHT:
			position.x += movementSpeed;
			break;
		case VK_UP:
			position.y -= movementSpeed;
			break;
		case VK_DOWN:
			position.y += movementSpeed;
			break;
		}
		//	Default handling for other messages.
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
//--------------------------------------------------------------------

//	use int main if you want to have a console to print out message
//int main()

WNDCLASS registerWindow(HINSTANCE hInstance) {

	/*
		Step 1
		Define and Register a Window.
	*/

	//	Window's structure
	WNDCLASS wndClass;
	//	Sset all members in wndClass to 0.
	ZeroMemory(&wndClass, sizeof(wndClass));

	//	Filling wndClass. You are to refer to MSDN for each of the members details.
	//	These are the fundamental structure members to be specify, in order to create your window.
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITEONBLACK);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hInstance = GetModuleHandle(NULL);
	wndClass.lpfnWndProc = WindowProcedure;
	wndClass.lpszClassName = "My Window";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//	Register the window.
	RegisterClass(&wndClass);


	return wndClass;
}

void createWindow(WNDCLASS wndClass, HINSTANCE hInstance) {
	/*
		Step 2
		Create the Window.
	*/
	//	You are to refer to MSDN for each of the parameters details.
	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "Valorant 2", WS_OVERLAPPEDWINDOW, 0, 100, 800, 700, NULL, NULL, GetModuleHandle(NULL), NULL);
	ShowWindow(g_hWnd, 1);

	//Arrow Cursor
	HCURSOR hSwordCursor = (HCURSOR)LoadImage(NULL, "pointer.png", IMAGE_CURSOR, 0, 0, LR_LOADFROMFILE);
	if (hSwordCursor) {
		SetClassLongPtr(g_hWnd, GCLP_HCURSOR, (LONG_PTR)hSwordCursor);
	}
	//	Some interesting function to try out.
	//	ShowCursor(false);
}

void CreateDirectInput() {
	//	Direct Input keyboard device.
	hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);

	//	Direct Input mouse device.
	hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput2, NULL);

	//	Create the keyboard device.
	hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);

	//	Create the mouse device
	hr = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);

	//	Set the input data format.
	dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	dInputMouseDevice->SetDataFormat(&c_dfDIMouse);

	//	Set the cooperative level.
	//	To Do:
	//	Try with different combination.
	dInputKeyboardDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	dInputMouseDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	/*---
		For buffered data
		//	Define buffer for input.
		//const int DEVICE_BUFFER_SIZE = 4;
		//DIDEVICEOBJECTDATA deviceBuffer[DEVICE_BUFFER_SIZE];

		////	Set the event buffer / properties.
		//DIPROPDWORD dipdw;
		//dipdw.diph.dwSize = sizeof(DIPROPDWORD);
		//dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		//dipdw.diph.dwObj = 0;
		//dipdw.diph.dwHow = DIPH_DEVICE;
		//dipdw.dwData = DEVICE_BUFFER_SIZE;

		//hr = dInputKeyboardDevice->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	--*/
	dInputKeyboardDevice->Acquire();
	dInputMouseDevice->Acquire();
}

bool handleWindowMsg(MSG msg) {
	/*
		Step 3
		Handling window messages
		NOTE! There are several ways of writing the message loop.
		You have to based on which kind of application your are writing.
	*/
	/*
		The if- version process one message per one iteration loop
		The while- version will clear the message queue before dealing with your own code.

		Another function is GetMessage.
		This function is not suitable for game, because it will block your program until it recieves a message.
		your code will only executed when you have messages, otherwies your pogram will be waiting... (similar to cin)
		Suitable for event based program, such as bussiness app.
	*/
	//	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		//	Receive a quit message

		if (msg.message == WM_QUIT) {
			return false;
		}
		else {
			//	Translate the message 
			TranslateMessage(&msg);
			//	Send message to your window procedure
			DispatchMessage(&msg);
		}

		/*
			Write your code here...
		*/

	}
	return true;
}

void closewindow(HINSTANCE hInstance) {
	//	Free up the memory.
	UnregisterClass(wndClass.lpszClassName, hInstance);
}
LPD3DXSPRITE sprite = NULL;
//	use WinMain if you don't want the console

void createFontBrush()
{
	//Create font. Study the documentation
	HRESULT hr = D3DXCreateFont(d3dDevice, 25, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &fontBrush);

	textRect.left = 100;
	textRect.top = 100;
	textRect.right = 150;
	textRect.bottom = 125;
}

void cleanUpBrush()
{
	//Clean Up
}

int createDirectX() {
	//	Define how the screen presents.
	ZeroMemory(&d3dPP, sizeof(d3dPP));

	d3dPP.Windowed = true;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = 1280;
	d3dPP.BackBufferHeight = 800;
	d3dPP.hDeviceWindow = g_hWnd;

	HRESULT hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);

	if (FAILED(hr)) {
		return 0;
	}
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASS test = registerWindow(hInstance);

	//same like this
	//int* x = new int(5);

	//Ensure window is created successfully then only create D3D9 device.
	createWindow(test, hInstance);
	if (createDirectX() != 0) {
		return 0;
	}
	//	Define how the screen presents.
	D3DPRESENT_PARAMETERS d3dPP;
	ZeroMemory(&d3dPP, sizeof(d3dPP));

	//	Refer to Direct3D 9 documentation for the meaning of the members.
	d3dPP.Windowed = true;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = 800;
	d3dPP.BackBufferHeight = 700;
	d3dPP.hDeviceWindow = g_hWnd;

	//Ensure window is created successfully then only create D3D9 device.
	createWindow(test, hInstance);
	if (createDirectX() != 0) {
		return 0;
	}

	//	Create a Direct3D 9 device.
	HRESULT hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);
	//like direct3D9.CreateDevice(...) then HRESULT hr will just reply success or fail,  so parameter &d3dDevice to tell createDevice and put at the table
	D3DXCreateSprite(d3dDevice, &sprite);
	createFontBrush();

	//	To Do: Cout out the message to indicate the failure.
	if (FAILED(hr))
	{
		return 0;
	}

	//	Initialization
	LPDIRECT3DTEXTURE9 cursortexture = NULL;

	//	Create sprite. Study the documentation. 
	hr = D3DXCreateSprite(d3dDevice, &spritebrush);
	D3DXCreateTextureFromFile(d3dDevice, "bg1.png", &texture1);
	D3DXCreateTextureFromFile(d3dDevice, "bg2.png", &texture2);
	D3DXCreateTextureFromFile(d3dDevice, "bg3.png", &texture3);
	D3DXCreateTextureFromFileEx(d3dDevice, "04.bmp", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 128, 64),
		NULL, NULL, &pic1);
	/*hr = D3DXCreateTextureFromFileEx(d3dDevice, "04.bmp", D3DX_DEFAULT, D3DX_DEFAULT,
	D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
	D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 128, 64),
	NULL, NULL, & texture4);*/
	D3DXCreateTextureFromFileEx(d3dDevice, "numbers.bmp", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 128, 0),
		NULL, NULL, &pic2);


	LPD3DXFONT font = NULL;
	//	Create font. Study the documentation.
	hr = D3DXCreateFont(d3dDevice, 30, 0, FW_NORMAL, 1, FALSE,
		DEFAULT_CHARSET, OUT_TT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &font);

	RECT textRect;
	textRect.left = 100;
	textRect.top = 100;
	textRect.right = 1000;
	textRect.bottom = 1000;

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	CreateDirectInput();

	//	Key input buffer
	BYTE  diKeys[256];

	while (handleWindowMsg(msg))
	{
		GetCursorPos(&mousePos);
		D3DXVECTOR3 cursorPos((float)mousePos.x, (float)mousePos.y, 0.0f);

		//	Clear the back buffer.
		d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(colournum1, colournum2, colournum3), 1.0f, 0);

		//	Begin the scene
		d3dDevice->BeginScene();

		//	Specify alpha blend will ensure that the sprite will render the background with alpha.
		spritebrush->Begin(D3DXSPRITE_ALPHABLEND);

		//	Sprite rendering. Study the documentation.
		spritebrush->Draw(*texturenum, NULL, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

		RECT picRect;
		picRect.left = piccol * 32;
		picRect.top = picrow * 32;
		picRect.right = picRect.left + 32;
		picRect.bottom = picRect.top + 32;
		spritebrush->Draw(pic1, &picRect, NULL, &vector1, D3DCOLOR_XRGB(255, 255, 255));

		RECT numRect;
		numRect.left = numcol * 32;
		numRect.top = numrow * 32;
		numRect.right = numRect.left + 32;
		numRect.bottom = numRect.top + 32;
		spritebrush->Draw(pic2, &numRect, NULL, &vector2, D3DCOLOR_XRGB(255, 255, 255));
		//sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOzR_XRGB(255, 255, 255));
		//sprite->Draw(texture, &spriteRect, NULL, &D3DXVECTOR3(32, 32, 0), D3DCOLOR_XRGB(255, 255, 255));

		RECT testRect;
		testRect.left = testcol * 85;
		testRect.top = testrow * 65;
		testRect.right = testRect.left + 85;
		testRect.bottom = testRect.top + 65;
		spritebrush->Draw(test1, &testRect, NULL, &vector3, D3DCOLOR_XRGB(255, 255, 255));

		dInputKeyboardDevice->GetDeviceState(256, diKeys);

		if (diKeys[DIK_UP] & 0x80)
		{
			cout << "UP" << endl;
		}

		dInputMouseDevice->GetDeviceState(sizeof(mousestate), &mousestate);
		xPos += mousestate.lX;
		yPos += mousestate.lY;
		textx = to_string(xPos);
		texty = to_string(yPos);
		vectortext = "X: " + textx + "    Y: " + texty;
		strncpy_s(vectorchar, vectortext.c_str(), sizeof(vectorchar));

		sprite->Begin(D3DXSPRITE_ALPHABLEND);

		font->DrawText(spritebrush, vectorchar, -1, &textRect, 0, D3DCOLOR_XRGB(255, 255, 255));

		sprite->End();
		//	End sprite drawing
		spritebrush->End();


		//	End the scene
		d3dDevice->EndScene();

		//	Present the back buffer to screen
		d3dDevice->Present(NULL, NULL, NULL, NULL);
	}

	//	Release keyboard device.
	dInputKeyboardDevice->Unacquire();
	dInputKeyboardDevice->Release();
	dInputKeyboardDevice = NULL;

	//	Release DirectInput.
	dInput->Release();
	dInput = NULL;

	font->Release();
	font = NULL;

	spritebrush->Release();
	spritebrush = NULL;

	//	Release the device when exiting.
	d3dDevice->Release();
	//	Reset pointer to NULL, a good practice.
	d3dDevice = NULL;

	//	Free up the memory.
	UnregisterClass(test.lpszClassName, hInstance);

	return 0;
}
//--------------------------------------------------------------------
