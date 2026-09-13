//	Ask the compiler to include minimal header files for our program.
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <d3d9.h>// need to configure vs
#include <d3dx9.h>
#include <iostream>
#include <random>
#include <vector>
#include <dinput.h>
#include <string>
#include <cmath>
#include "timer.h"
#include "Drawss.h"
#include "Game.h"

using namespace std;

#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"d3d9.lib")//only work for window (same like p2t2q2)
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

//--------------------------------------------------------------------
WNDCLASS wndClass;

int windowwidth = 1920;
int windowheight = 1080;

MSG msg;

timer frametimer;

// Initialization	GraphicCard
IDirect3DDevice9* d3dDevice;

//	Initialization	sprite
LPDIRECT3DTEXTURE9 texture = NULL;
LPDIRECT3DTEXTURE9 texture2 = NULL;
LPDIRECT3DTEXTURE9 texture3 = NULL;
LPDIRECT3DTEXTURE9 cp = NULL;
LPDIRECT3DTEXTURE9 prot = NULL;
LPDIRECT3DTEXTURE9 bg = NULL;
LPDIRECT3DTEXTURE9 pullicon = NULL;
LPDIRECT3DTEXTURE9 xicon = NULL;
LPDIRECT3DTEXTURE9 hutao = NULL;
LPDIRECT3DTEXTURE9 yelan = NULL;
LPDIRECT3DTEXTURE9 homa = NULL;
LPDIRECT3DTEXTURE9 cui = NULL;
LPDIRECT3DTEXTURE9 bui = NULL;

LPD3DXSPRITE spritebrush = NULL;
LPD3DXFONT fontbrush = NULL;
LPDIRECTINPUT8 dInput;
//	Key input buffer
BYTE  dikeys[256];

LPDIRECTINPUTDEVICE8  dInputKeyboardDevice;		//	Direct Input keyboard device.
LPDIRECTINPUTDEVICE8  dInputMouseDevice;		//	Direct Input mouse device.
DIMOUSESTATE mousestate;	
LPD3DXLINE linebrush = NULL;

D3DXVECTOR3 position4 = D3DXVECTOR3(100, 300, 0);
D3DXVECTOR3 positionrighttop = D3DXVECTOR3(1780, 10, 0);
D3DXVECTOR3 positionrighttop1 = D3DXVECTOR3(1680, 10, 0);
D3DXVECTOR3 positionrighttop2 = D3DXVECTOR3(1580, 10, 0);
D3DXVECTOR3 positionhutao = D3DXVECTOR3(595, 50, 0);
D3DXVECTOR3 positionyelan = D3DXVECTOR3(910, 50, 0);
D3DXVECTOR3 positionhoma = D3DXVECTOR3(1250, 50, 0);
D3DXVECTOR3 positionmlt = D3DXVECTOR3(1200, 500, 0);
D3DXVECTOR2 positiontb1(600, 600);
D3DXVECTOR2 positiontb2(500, 500);

RECT textRect = { 1350,820,1650,1320 };
//textRect.left = 1350;
//textRect.top = 820;
//textRect.right = 1650;
//textRect.bottom = 1320;

RECT textrect1 = { 1121,820,1653,1320 };
RECT textrect2 = { 521,820,1653,1320 };
RECT collisionrectmlt = { 0,0, 0, 0 };
RECT collision2 = { 0,0, 0, 0};

//	Window handle
HWND g_hWnd = NULL;
//--------------------------------------------------------------------

int color, red = 162, green = 162, blue = 162, colorIncreaseRate = 5, clockx = 0, clocky = 0, fclockx = 0, fclocky = 0, radius = 200, xclockx = 0, xclocky = 0, fxclockx = 0, fxclocky = 0,centerx=900,centery=400,speed=5,globalframe=0;
float angle = 0.0, xangle = 0.0, ball1angle = 0.0f, ball1angle2 = 0.0f;
bool colorflag, redflag = true, blueflag = true, greenflag = true,showbg1 = false,showbg2 = false,showbg3 = false,showwalk = false, showatk = false, showprot = false,isfs =false;
POINT mousep = { 0,0 };

enum Plystate {
	STAND,
	WALK,
	ATTACK,
	PROTECT
};

Plystate currentState = STAND;

enum Scene {
	DEF,
	PULL,
	CRT,
	BAG
};

Scene currentScene = DEF;

Drawss drawit(0,0, 2, 2, 32, 32,0,0);
Drawss drawnum(0,0, 4, 4, 32, 32,0,0);
Drawss drawfwwalk(0,0, 8, 1, 194, 213, 217, 220);
Drawss drawfwatk(0, 0,4, 1, 240, 175, 208, 719);
Drawss drawfwprt(0, 0,4, 1, 240, 175, 208, 719);
Drawss drawmonster(0,0, 4, 1, 240, 175, 208, 719);
Drawss drawbanner(0, 0, 1, 3, 1600, 900, 0, 0);
Drawss drawmlt(0, 0, 4, 4, 32, 49, 0, 0);
Drawss drawtb1(0, 0, 1, 2, 32, 32, 0, 0);
Drawss drawtb2(0,0,1,2,32,32,32,0);

class Character {
	private:
		string name;
		int maxhp;
		int maxatk;
		int maxdef;
		int element;
		int star;
	public:
		Character() {
			name = "";
			maxhp = 0;
			maxatk = 0;
			maxdef = 0;
			element = 1;
			star = 4;
		}
		Character(string n, int mhp,int matk,int mdef,int e,int s) {
			name = n;
			maxhp = mhp;
			maxatk = matk;
			maxdef = mdef;
			element = e;
			star = s;
		}
		int getstar() {
			return star;
		}
		int getelement() {
			return element;
		}
		string tostring() {
			return name;
		}
};

// 1 pyro 
// 2 hydro 
// 3 lei 
// 4 cryo 
// 5 grass
// 6 geo 
// 7 wind
vector<Character> characters = {
	Character("Hutao",1200,512,164,1,5),
	Character("Yelan",1300,912,164,2,5),
	Character("Diluc",1400,612,164,1,5),
	Character("Xingqiu",1500,212,164,2,4),
	Character("Beidou",1500,212,164,3,4),
	Character("Ningguang",1500,212,164,6,4),
	Character("Xiangling",1500,212,164,1,4),
	Character("Thoma",1500,212,164,1,4),
	Character("Noelle",1500,212,164,6,4),
	Character("Kachina",1500,212,164,6,4)
};

Character currentchrt;

class Weapon {
	private:
		string name;
		string mainstat;
		int mainstatnum;
		string substat;
		int substatnum;
		int star;
	public:
		Weapon() {
			name = "";
			mainstat = "";
			mainstatnum = 0;
			substat = "";
			substatnum = 0;
			star = 3;
		}
		Weapon(string n, int s) {
			name = n;
			mainstat = "";
			mainstatnum = 0;
			substat = "";
			substatnum = 0;
			star = s;
		}
		int getstar() {
			return star;
		}
		string tostring() {
			return "Name: " + name;
		}
};

vector<Weapon> weapons = {
	Weapon("Homa",5),
	Weapon("Sacrificial Sword",4),
	Weapon("Rust",4),
	Weapon("Eye of Perception",4),
	Weapon("The Flute",4),
	Weapon("slingshot",3),
	Weapon("Harbinger of Dawn",3),
	Weapon("Debate Club",3),
	Weapon("Bloodtainted Greatsword",3),
	Weapon("Ferrous Shadow",3)
};

class Player {
	private:
		int mspeed;
		vector<Character> plycharacter;
		vector<Weapon> plyweapon;
		bool guarantee;
	public:	
		Player() {
			mspeed = 5;
			guarantee = false;
		}
		vector<Character> getplycharacter()const {
			return plycharacter;
		}

		void setplycharacter(Character newcharacter) {
			plycharacter.push_back(newcharacter);
		}

		void setplyweapon(Weapon newweapon) {
			plyweapon.push_back(newweapon);
		}

		bool getguarantee() {
			return guarantee;
		}
		void setguarantee(bool gua) {
			guarantee = gua;
		}

		void walking(int direction) {

			if (direction == 1) {
				position4.y -= mspeed;
			}
			else if (direction == 2) {
				position4.x -= mspeed;
			}
			else if (direction == 3) {
				position4.y += mspeed;
			}
			else {
				position4.x += mspeed;
			}

			/*showstd = false;
			showwalk = true;*/
			showwalk = true;
			currentState = WALK;

			drawfwwalk.setframe(drawfwwalk.getframe() + 1);
			if (drawfwwalk.getframe() >= drawfwwalk.getcol() * drawfwwalk.getrow()) {
				drawfwwalk.setframe(0);
			}
		}
		void attack() {

			/*showstd = !showstd;
			showatk = !showatk;*/
			showatk = true;
			currentState = ATTACK;
			
			drawfwwalk.setframe(0);
			/*drawfwatk.setframe(drawfwatk.getframe() + 1);
			if (drawfwatk.getframe() >= drawfwatk.getcol() * drawfwatk.getrow()) {
				drawfwatk.setframe(drawfwatk.getframe() - 1);
			}*/
			
		}
		void protect() {
			showprot = true;
			currentState = PROTECT;
			drawfwwalk.setframe(0);
		}
};

Player ply1;

class Pullsystem {
	private:
		int count4star;
		int count5star;
		int countpull;
		random_device rd;
		mt19937 gen;
		uniform_int_distribution<int>dis;

	public:
		Pullsystem() :gen(rd()),dis(0, 100)
		{
			count4star = 1;
			count5star = 1;
			countpull = 1;	
		}

		void pull4() {
			/*vector<string> p4star = {
				"Beidou","Ningguang","Xingqiu","Sacrificial Sword","Xiangling","Thoma","Noelle","Kachina","Rust","Eye of Perception","The Flute"
			};*/

			vector<Character> p4star;
			for (int i = 0; i < characters.size(); i++) {
				if (characters[i].getstar() == 4) {
					p4star.push_back(characters[i]);
				}
			}

			vector<Weapon> p4starw;
			for (int i = 0; i < weapons.size(); i++) {
				if (weapons[i].getstar() == 4) {
					p4starw.push_back(weapons[i]);
				}
			}

			uniform_int_distribution<int>cw(0,2);
			int cws = cw(gen);

			if (cws > 1) {
				uniform_int_distribution<int>p4(0, p4starw.size() - 1);
				int p4s = p4(gen);
				Weapon gotitem = p4starw[p4s];
				cout << countpull << ": 4 Star: " << gotitem.tostring() << endl;
				ply1.setplyweapon(gotitem);
			}
			else {
				uniform_int_distribution<int>p4(0, p4star.size() - 1);
				int p4s = p4(gen);
				Character gotitem = p4star[p4s];
				cout << countpull << ": 4 Star: " << gotitem.tostring() << endl;
				ply1.setplycharacter(gotitem);
			}
			

		}

		void pull5() {
			Character gotitem;
			Weapon gotweapon;

			if (!ply1.getguarantee()) {
				int losen = dis(gen);
				if (losen <= 50) {
					gotitem = characters[2];
					ply1.setguarantee(true);
				}
			}

			ply1.setguarantee(false);
			switch (drawbanner.getframe()) {
			case 0:
				gotitem = characters[0];
				break;
			case 1:
				gotitem = characters[1];
				break;
			case 2:
				gotweapon = weapons[0];
				break;
			}

			cout << countpull << ": 5 Star: " << gotitem.tostring() << endl;
			ply1.setplycharacter(gotitem);
		}

		void pulling(int p) {
			Weapon gotitem;
			/*vector<string> p3star = {
				"slingshot","Harbinger of Dawn","Debate Club","Bloodtainted Greatsword","Ferrous Shadow"
			};*/
			vector<Weapon> p3star;
			for (int i = 0; i < weapons.size(); i++) {
				if (weapons[i].getstar() == 3) {
					p3star.push_back(weapons[i]);
				}
			}

			uniform_int_distribution<int>p3(0, p3star.size() - 1);

			for (int i = 0; i < p; i++) {
				//cout << "count4star: "<< count4star << endl;
				//cout << "count5star: "<< count5star << endl;

				if (count5star == 90) {
					count5star = 1;
					pull5();
				}
				else if (count4star == 10) {
					count4star = 1;
					pull4();
				}
				else {
					int ip = dis(gen);
					//cout << "345star: "<< ip << endl;
					if (ip < 80) {
						int p3s = p3(gen);
						//cout << "which 3star: " << p3s << endl;

						gotitem = p3star[p3s];

						cout << countpull << ": 3 Star: " << gotitem.tostring() << endl;
						ply1.setplyweapon(gotitem);
					}
					else if (ip > 80) {
						count4star = 0;
						pull4();
					}
					else {
						count5star = 0;
						pull5();
					}
					count4star++;
					count5star++;
				}
				countpull++;
			}

		}
};

Pullsystem pullit;

class UpdateDI {
	private:
		POINT mousep = { 0,0 };
	public:
		POINT getmousep() {
			return mousep;
		}
		void setmousep(int mx, int my) {
			mousep = { mx,my };
		}
		string updateto_string() {
			return "Mouse X: " + to_string(mousep.x) + " Mouse Y: " + to_string(mousep.y) + "\n";
		}
};

void ir(int& color, bool& colorflag) {
	color += colorIncreaseRate;
	if (color > 254) {
		colorflag = false;
	}
}

void dr(int& color, bool& colorflag) {
	color -= colorIncreaseRate;
	if (color < 1) {
		colorflag = true;
	}
}

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
		case 'N':
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
		case '1':
			if (showbg2 || showbg3) {
				showbg2 = false;
				showbg3 = false;
			}
			showbg1 = !showbg1;
			break;
		case '2':
			if (showbg1 || showbg3) {
				showbg1 = false;
				showbg3 = false;
			}
			showbg2 = !showbg2;
			break;
		case '3':
			if (showbg1 || showbg2) {
				showbg1 = false;
				showbg2 = false;
			}
			showbg3 = !showbg3;
			break;
		case 'W':
			if (!showatk && !showprot) {
				ply1.walking(1);
			}
			break;
		case 'A':
			if (!showatk && !showprot) {
				ply1.walking(2);
			}
			break;
		case 'S':
			if (!showatk && !showprot) {
				ply1.walking(3);
			}
			break;
		case 'D':
			if (!showatk && !showprot) {
				ply1.walking(4);
			}
			break;
		case 'T':
			drawit.setframe(drawit.getframe() + 1);
			drawnum.setframe(drawnum.getframe() + 1);
			if (drawit.getframe() >= drawit.getcol() * drawit.getrow()) {
				drawit.setframe(0);
			}
			if (drawnum.getframe() >= drawnum.getcol() * drawnum.getrow()) {
				drawnum.setframe(0);
			}
			break;
		case 'C':
			if (currentScene == DEF) {
				currentScene = CRT;
			}
		case 'B':
			if (currentScene == DEF) {
				currentScene = BAG;
			}
		case 'P':
			pullit.pulling(1);
			break;
		case 'O':
			pullit.pulling(10);
			break;
		case VK_F3:
			if (currentScene == DEF) {
				currentScene = PULL;
			}
			else {
				currentScene = DEF;
			}break;
		}break;
	case WM_KEYUP:
		switch (wParam) {
		case 'W':
		case 'A':
		case 'S':
		case 'D':
			/*showwalk = false;
			showstd = true;*/ //old way
			showwalk = false;
			if (!showatk) {
				currentState = STAND;
				drawfwwalk.setframe(0);
			}
			break;
		}break;
		
		//cout << "Red: " << red << "Green: " << green << "blue: " << blue << endl;
		//	Default handling for other messages.

	//case WM_MOUSEMOVE: 
	//	mousep.x = LOWORD(lParam);
	//	mousep.y = HIWORD(lParam);
	//	//cout << "mouse x: " << mousep.x << " mouse y: " << mousep.y << endl;
	//	//ShowCursor(FALSE);

	//	break;
	case WM_LBUTTONDOWN:
		/*mousep.x = LOWORD(lParam);
		mousep.y = HIWORD(lParam);*/
		cout << "mouse x: " << mousep.x << " mouse y: " << mousep.y << endl;
		if (currentScene == DEF) {
			if (mousep.x >= positionrighttop2.x && mousep.x <= positionrighttop2.x + 100 && mousep.y >= positionrighttop2.y && mousep.y <= positionrighttop2.y + 100) {
				currentScene = PULL;
				break;
			}
		else {
			ply1.attack();
		}
		}
		if (currentScene == PULL) {
			if (mousep.x >= positionhutao.x && mousep.x <= positionhutao.x + 130 && mousep.y >= positionhutao.y && mousep.y <= positionhutao.y + 130) {
				drawbanner.setframe(0);
				break;
			}
			else if(mousep.x >= positionyelan.x && mousep.x <= positionyelan.x + 130 && mousep.y >= positionyelan.y && mousep.y <= positionyelan.y + 130) {
				drawbanner.setframe(1);
				break;
			}
			else if (mousep.x >= positionhoma.x && mousep.x <= positionhoma.x + 100 && mousep.y >= positionhoma.y && mousep.y <= positionhoma.y + 130) {
				drawbanner.setframe(2);
				break;
			}
			else if (mousep.x >= textRect.left && mousep.x <= textRect.right && mousep.y >= textRect.top && mousep.y <= textRect.bottom ) {
				pullit.pulling(10);
			}
		}
		break;
	case WM_LBUTTONUP:
		showatk = false;
		if (showwalk) {
			currentState = WALK;
			drawfwwalk.setframe(0);
		}
		else {
			currentState = STAND;
			drawfwwalk.setframe(0);
		}

		break;
	case WM_RBUTTONDOWN:
		ply1.protect();
		break;
	case WM_RBUTTONUP:
		showprot = false;
		if (showwalk) {
			currentState = WALK;
			drawfwwalk.setframe(0);
		}
		else {
			currentState = STAND;
			drawfwwalk.setframe(0);
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
//--------------------------------------------------------------------

//	use int main if you want to have a console to print out message
//int main()

void createwindow() {
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

	/*
		Step 2
		Create the Window.
	*/
	//	You are to refer to MSDN for each of the parameters details.
	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "My Window's Name", WS_OVERLAPPEDWINDOW, 0, 100, windowwidth, windowheight, NULL, NULL, GetModuleHandle(NULL), NULL);
	ShowWindow(g_hWnd, 1);

	//	Some interesting function to try out.
	//	ShowCursor(false);
}

bool runningwindow() {
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

bool createdx() {
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
	d3dPP.BackBufferWidth = windowwidth;
	d3dPP.BackBufferHeight = windowheight;
	d3dPP.hDeviceWindow = g_hWnd;

	//	Create a Direct3D 9 device.
	HRESULT hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);
	//like direct3D9.CreateDevice(...) then HRESULT hr will just reply success or fail,  so parameter &d3dDevice to tell createDevice and put at the table

	//	To Do: Cout out the message to indicate the failure.
	if (FAILED(hr))
		return false;	// or you can output a messagebox
}

void cleandx() {
	//	Release the device when exiting.
	d3dDevice->Release();
	//	Reset pointer to NULL, a good practice.
	d3dDevice = NULL;
}

void createsb() {

	//	Create sprite. Study the documentation. 
	HRESULT hr = D3DXCreateSprite(d3dDevice, &spritebrush);
	 
	string assetspic = "assets\\newbg1.png";
	//	Create texture. Study the documentation.
	if(FAILED(D3DXCreateTextureFromFileEx(d3dDevice, assetspic.c_str(), D3DX_DEFAULT, D3DX_DEFAULT,
										D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, 
										D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(153, 217, 234), 
										NULL, NULL, &texture))){
		MessageBox(NULL, "No texture1!", "ERROR", MB_OK);
	}

	/*if (FAILED(D3DXCreateTextureFromFile(d3dDevice, "assets\\newbg1.png", &texture))) {
		MessageBox(NULL, "No texture1!", "ERROR", MB_OK);
	}*/

	if (FAILED(D3DXCreateTextureFromFileEx(d3dDevice, "assets\\newbg2.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(200, 191, 231),
		NULL, NULL, &texture2))) {
		MessageBox(NULL, "No texture2!", "ERROR", MB_OK);
	}

	if (FAILED(D3DXCreateTextureFromFileEx(d3dDevice, "assets\\newbg3.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(181, 230, 29),
		NULL, NULL, &texture3))) {
		MessageBox(NULL, "No texture3!", "ERROR", MB_OK);
	}

	if (FAILED(D3DXCreateTextureFromFileEx(d3dDevice, "assets\\newfw2.jpg", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(162,162,162),
		NULL, NULL, drawfwwalk.gettextureptr()))) {
		MessageBox(NULL, "No warrior!", "ERROR", MB_OK);
	}

	if (FAILED(D3DXCreateTextureFromFileEx(d3dDevice, "assets\\newpointer.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(162, 162, 162),
		NULL, NULL, &cp))) {
		MessageBox(NULL, "No pointer!", "ERROR", MB_OK);
	}

	if (FAILED(D3DXCreateTextureFromFileEx(d3dDevice, "assets\\04.bmp", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 128, 64),
		NULL, NULL, drawit.gettextureptr()))) {
		MessageBox(NULL, "No 04!", "ERROR", MB_OK);
	}

	if (FAILED(D3DXCreateTextureFromFileEx(d3dDevice, "assets\\numbers.bmp", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 128, 0),
		NULL, NULL, drawnum.gettextureptr()))) {
		MessageBox(NULL, "No number!", "ERROR", MB_OK);
	}

	if (FAILED(D3DXCreateTextureFromFileEx(d3dDevice, "assets\\protect.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0),
		NULL, NULL, &prot))) {
		MessageBox(NULL, "No protect!", "ERROR", MB_OK);
	}

	if (FAILED(D3DXCreateTextureFromFileEx(d3dDevice, "assets\\monster.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 128, 0),
		NULL, NULL, drawmonster.gettextureptr()))) {
		MessageBox(NULL, "No monster!", "ERROR", MB_OK);
	}

	if (FAILED(D3DXCreateTextureFromFileEx(d3dDevice, "assets\\pullbg.jpeg", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 0, 0),
		NULL, NULL, &bg))) {
		MessageBox(NULL, "No pullbg!", "ERROR", MB_OK);
	}

	if (FAILED(D3DXCreateTextureFromFileEx(d3dDevice, "assets\\pullicon2.jpg", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(256, 0, 0),
		NULL, NULL, &pullicon))) {
		MessageBox(NULL, "No pullicon!", "ERROR", MB_OK);
	}

	if (FAILED(D3DXCreateTextureFromFileEx(d3dDevice, "assets\\banner.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 120, 0),
		NULL, NULL, drawbanner.gettextureptr()))) {
		MessageBox(NULL, "No pullbanner!", "ERROR", MB_OK);
	}

	if (FAILED(D3DXCreateTextureFromFileEx(d3dDevice, "assets\\hutao.jpg", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 120, 0),
		NULL, NULL, &hutao))) {
		MessageBox(NULL, "No hutao!", "ERROR", MB_OK);
	}
	if (FAILED(D3DXCreateTextureFromFileEx(d3dDevice, "assets\\yelan.jpg", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 120, 0),
		NULL, NULL, &yelan))) {
		MessageBox(NULL, "No yelan!", "ERROR", MB_OK);
	}
	if (FAILED(D3DXCreateTextureFromFileEx(d3dDevice, "assets\\homa.jpg", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(0, 120, 0),
		NULL, NULL, &homa))) {
		MessageBox(NULL, "No homa!", "ERROR", MB_OK);
	}
	if (FAILED(D3DXCreateTextureFromFileEx(d3dDevice, "assets\\characterui.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(186, 95, 111),
		NULL, NULL, &cui))) {
		MessageBox(NULL, "No cui!", "ERROR", MB_OK);
	}
	string teststring = "assets\\bagui.png";
	if (FAILED(D3DXCreateTextureFromFileEx(d3dDevice,teststring.c_str(), D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(185, 93, 110),
		NULL, NULL, &bui))) {
		MessageBox(NULL, "No bui!", "ERROR", MB_OK);
	}

	if (FAILED(D3DXCreateTextureFromFileEx(d3dDevice, "assets\\militia.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(185, 93, 110),
		NULL, NULL, drawmlt.gettextureptr()))) { 
		MessageBox(NULL, "No Militia!", "ERROR", MB_OK);
	}

	if (FAILED(D3DXCreateTextureFromFileEx(d3dDevice, "assets\\twoball.png", D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(185, 93, 110),
		NULL, NULL, drawtb1.gettextureptr()))) {
		MessageBox(NULL, "No ball1!", "ERROR", MB_OK);
	}
	
}

void cleansb() {
	spritebrush->Release();
	spritebrush = NULL;

	texture->Release();
	texture = NULL;
}

void createfont() {
	HRESULT hr = D3DXCreateFont(d3dDevice, 45, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Arial", &fontbrush);
}
void cleanfont() {
	fontbrush->Release();
	fontbrush = NULL;
}

void createdi() {
	//	Direct Input object.
	LPDIRECTINPUT8 dInput;

	//	Create the Direct Input object.
	HRESULT hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);

	//	Create the keyboard device.
	hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);

	hr = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);

	//	Set the input data format.
	dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	dInputMouseDevice->SetDataFormat(&c_dfDIMouse);

	//	Set the cooperative level.
	//	To Do:
	//	Try with different combination.
	dInputKeyboardDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	dInputMouseDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	
}

void cleandi() {
	//	Release keyboard device.
	dInputKeyboardDevice->Unacquire();
	dInputKeyboardDevice->Release();
	dInputKeyboardDevice = NULL;

	dInputMouseDevice->Unacquire();
	dInputMouseDevice->Release();
	dInputMouseDevice = NULL;

	//	Release DirectInput.
	dInput = NULL;
}

void createline() {
	HRESULT hr = D3DXCreateLine(d3dDevice, &linebrush);
}

void cleanline() {
	linebrush->Release();
	linebrush = NULL;
}
void defscene() {

	RECT rectscreen;
	GetClientRect(g_hWnd, &rectscreen);
	float actwidth = rectscreen.right - rectscreen.left;
	float actheight = rectscreen.bottom - rectscreen.top;
	float scalex = actwidth / windowwidth;
	float scaley = actheight / windowheight;
	float finalscale = min(scalex, scaley);
	float offsetx = (actwidth - windowwidth * finalscale) / 2.0;
	float offsety = (actheight - windowheight * finalscale) / 2.0;
	D3DXVECTOR2 screenscale(finalscale, finalscale);
	D3DXVECTOR2 screentranlate(offsetx, offsety);

	//	Clear the back buffer.
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(red, green, blue), 1.0f, 0);

	//	Begin the scene
	d3dDevice->BeginScene();

	//	Clear and begin scene

	//	Specify alpha blend will ensure that the sprite will render the background with alpha.
	spritebrush->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMATRIX oldmat;
	spritebrush->GetTransform(&oldmat);

	/*if (angle == 360) {
		angle = 0;
	}*/
	
	clockx = centerx + (radius - 20) * sin(angle);
	clocky = centery + (radius - 20) * cos(angle);
	xclockx = centerx + (radius - 80) * -sin(xangle);
	xclocky = centery + (radius - 80) * cos(xangle);
	
	D3DXVECTOR2 lineVertices[] = { D3DXVECTOR2(xclockx, xclocky), D3DXVECTOR2(centerx, centery),D3DXVECTOR2(centerx, centery),D3DXVECTOR2(clockx, clocky) };

	linebrush->SetWidth(15);
	linebrush->Begin();
	linebrush->Draw(lineVertices, 4, D3DCOLOR_XRGB(0, 0, 0));
	
	float fangle = 0.0, fxangle = 0.0;
	for (int i = 0; i < 12; i++) {
		//if (fangle > 360) {
		//	fangle = 0;
		//	//fxangle = 0;
		//}
		fangle += D3DXToRadian(30.0f);
		//fxangle += D3DXToRadian(30.0f);
		fclockx = centerx + radius * sin(fangle);
		fclockx = centerx + radius * sin(fangle);
		fclocky = centery + radius * cos(fangle);
		fxclockx = centerx + (radius+100) * sin(fangle) ;
		fxclocky = centery + (radius + 100) * cos(fangle);

		D3DXVECTOR2 lineVertices2[] = { D3DXVECTOR2(fxclockx, fxclocky),D3DXVECTOR2(fclockx, fclocky) };
		linebrush->Draw(lineVertices2, 2, D3DCOLOR_XRGB(0, 0, 0));
	}

	D3DXMATRIX matscalescreen;
	D3DXMatrixTransformation2D(&matscalescreen,NULL,0.0,&screenscale, NULL, 0.0,NULL);
	spritebrush->SetTransform(&matscalescreen);

	/*D3DXMATRIX matscaleicon;
	D3DXMatrixScaling(&matscaleicon, 0.2, 0.2, 1.0);
	spritebrush->SetTransform(&matscaleicon);*/
	spritebrush->Draw(pullicon, NULL, NULL, &positionrighttop2, D3DCOLOR_XRGB(255, 255, 255));

	//	Specify the "	" rectangle.
	RECT spriteRect;
	spriteRect.left = 0;
	spriteRect.right = 400;
	spriteRect.top = 0;
	spriteRect.bottom = 300;

	D3DXVECTOR3 position = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 position2 = D3DXVECTOR3(400, 0, 0);
	D3DXVECTOR3 position3 = D3DXVECTOR3(400, 400, 0);
	D3DXVECTOR3 position04 = D3DXVECTOR3(500, 700, 0);
	D3DXVECTOR3 position05 = D3DXVECTOR3(700, 800, 0);
	D3DXVECTOR3 positioncp((float)mousep.x, (float)mousep.y, 0);

	//	Sprite rendering. Study the documentation.
	//spritebrush->Draw(texture, NULL(draw whole picture), NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	//sprite->Draw(texture, &spriteRect, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));
	if (showbg1) {
		spritebrush->Draw(texture, &spriteRect, NULL, &position, D3DCOLOR_XRGB(255, 255, 255));
	}

	if (showbg2) {
		spritebrush->Draw(texture2, &spriteRect, NULL, &position2, D3DCOLOR_XRGB(255, 255, 255));
	}

	if (showbg3) {
		spritebrush->Draw(texture3, &spriteRect, NULL, &position3, D3DCOLOR_XRGB(255, 255, 255));
	}

	//RECT spriteRectstd = { 222,0,426,222 };
	////RECT spriteRectwalk = { 457,220,589,434 };
	////RECT spriteRectwalk = { 266,218,447,431 };
	//RECT spriteRectatk = { 666,716,923,938 };

	//if(showstd){
	//	spritebrush->Draw(drawfwwalk.gettexture(), &spriteRectstd, NULL, &position4, D3DCOLOR_XRGB(255, 255, 255));
	//}
	//if (showwalk) {
	//	RECT spriteRectwalk = drawfwwalk.getrectbox();
	//	spritebrush->Draw(drawfwwalk.gettexture(), &spriteRectwalk, NULL, &position4, D3DCOLOR_XRGB(255, 255, 255));
	//}
	//if (showatk) {
	//	//RECT spriteRectatk = drawfwatk.getrectbox();
	//	spritebrush->Draw(drawfwwalk.gettexture(), &spriteRectatk, NULL, &position4, D3DCOLOR_XRGB(255, 255, 255));
	//}

	RECT spriteRectstate;

	switch (currentState) {
	case STAND:
		spriteRectstate = { 222,0,426,222 };
		break;

	case WALK:
		spriteRectstate = drawfwwalk.getrectbox();
		break;

	case ATTACK:
		spriteRectstate = { 666,716,923,938 };
		break;

	case PROTECT:
		spriteRectstate = { 1021,0,1203,222 };
		break;
	};
	
	spritebrush->Draw(drawfwwalk.gettexture(), &spriteRectstate, NULL, &position4, D3DCOLOR_XRGB(255, 255, 255));


	spritebrush->Draw(cp, NULL, NULL, &positioncp, D3DCOLOR_XRGB(255, 255, 255));

	RECT r = drawmlt.getrectbox();
	spritebrush->Draw(drawmlt.gettexture(), &r, NULL, &positionmlt, D3DCOLOR_XRGB(255, 255, 255));
	
	//D3DXVECTOR2 ballscale(2.0f, 2.0f);
	D3DXVECTOR2 ballrotate1(drawtb1.getwidth() / 2, drawtb1.getheight() / 2);
	D3DXVECTOR2 ballrotate2(drawtb2.getwidth()/2, drawtb2.getheight()/ 2);

	D3DXMATRIX twoball1;
	D3DXMatrixTransformation2D(&twoball1, NULL, 0.0, NULL, &ballrotate1, ball1angle, &positiontb1);
	
	spritebrush->SetTransform(&twoball1);
	RECT r1 = drawtb1.getverticalrect();
	spritebrush->Draw(drawtb1.gettexture(), &r1, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	D3DXMATRIX twoball2;
	D3DXMatrixTransformation2D(&twoball2, NULL, 0.0, NULL, &ballrotate2 , ball1angle2, &positiontb2);

	RECT r2 = drawtb2.getverticalrect();

	spritebrush->SetTransform(&twoball2);
	spritebrush->Draw(drawtb2.gettexture(), &r2, NULL, NULL, D3DCOLOR_XRGB(255, 255, 255));

	spritebrush->SetTransform(&oldmat);

	spritebrush->Draw(cp, NULL, NULL, &positioncp, D3DCOLOR_XRGB(255, 255, 255));

	RECT spriteRect04 = drawit.getrectbox();
	RECT spriteRectnum = drawnum.getrectbox();

	//cout <<"w:" << w << " x:" << x << "y:" << y << "z:" << z << endl;

	spritebrush->Draw(drawit.gettexture(), &spriteRect04, NULL, &position04, D3DCOLOR_XRGB(255, 255, 255));
	spritebrush->Draw(drawnum.gettexture(), &spriteRectnum, NULL, &position05, D3DCOLOR_XRGB(255, 255, 255));

	spritebrush->Draw(cui, NULL, NULL, &positionrighttop, D3DCOLOR_XRGB(255, 255, 255));
	spritebrush->Draw(bui, NULL, NULL, &positionrighttop1, D3DCOLOR_XRGB(255, 255, 255));


	RECT textRect;
	textRect.left = 100;
	textRect.top = 100;
	textRect.right = 5000;
	textRect.bottom = 1250;
	string hw = "Mouse X: " + to_string(mousep.x) + " Mouse Y: " + to_string(mousep.y) + "\n";

	fontbrush->DrawText(spritebrush, hw.c_str(), hw.size(), &textRect,0, D3DCOLOR_XRGB(255, 255, 255));
	
	// End Line Brush
	linebrush->End();
	
	//	End sprite drawing
	spritebrush->End();

	//	End and present scene

	//	End the scene
	d3dDevice->EndScene();

	//	Present the back buffer to screen
	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void pullscene() {

	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(red, green, blue), 1.0f, 0);

	d3dDevice->BeginScene();

	spritebrush->Begin(D3DXSPRITE_ALPHABLEND);

	D3DXMATRIX oldmat;
	spritebrush->GetTransform(&oldmat);

	FLOAT scalebgx = (FLOAT)windowwidth / 1024;
	FLOAT scalebgy = (FLOAT)windowheight / 1024;
	D3DXMATRIX scalebg;
	D3DXVECTOR2 sbg = D3DXVECTOR2(scalebgx, scalebgy);

	D3DXMatrixTransformation2D(&scalebg, NULL, 0, &sbg, NULL, 0, NULL);
	spritebrush->SetTransform(&scalebg);

	D3DXVECTOR3 position = D3DXVECTOR3(0, 0, 0);

	spritebrush->Draw(bg, NULL, NULL, &position, D3DCOLOR_XRGB(255, 255, 255));
	
	//D3DXVECTOR3 positionx = D3DXVECTOR3((float)(windowwidth - 800) / 2, (float)(windowheight - 450) / 2, 0);
	D3DXVECTOR3 positionx = D3DXVECTOR3(560*2,315*2,0);
	RECT rectbanner = drawbanner.getrectbox();

	D3DXMATRIX matscale;
	D3DXMatrixScaling(&matscale, 0.5, 0.5, 1.0);
	spritebrush->SetTransform(&matscale);
	
	spritebrush->Draw(drawbanner.gettexture(), &rectbanner, NULL, &positionx, D3DCOLOR_XRGB(255, 255, 255));

	spritebrush->SetTransform(&oldmat);

	spritebrush->Draw(hutao, NULL, NULL, &positionhutao, D3DCOLOR_XRGB(255, 255, 255));
	spritebrush->Draw(yelan, NULL, NULL, &positionyelan, D3DCOLOR_XRGB(255, 255, 255));
	spritebrush->Draw(homa, NULL, NULL, &positionhoma, D3DCOLOR_XRGB(255, 255, 255));

	fontbrush->DrawText(spritebrush, "10 pull", 7, &textRect, DT_LEFT | DT_TOP, D3DCOLOR_XRGB(0, 0, 0));
	fontbrush->DrawText(spritebrush, "1 pull", 7, &textrect1, DT_LEFT | DT_TOP, D3DCOLOR_XRGB(0, 0, 0));
	fontbrush->DrawText(spritebrush, "History", 7, &textrect2, DT_LEFT|DT_TOP , D3DCOLOR_XRGB(0, 0, 0));
	
	spritebrush->End();

	d3dDevice->EndScene();

	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void characterscene() {
	switch(currentchrt.getelement()){
		case 1:
			red = 255;
			green = 0;
			blue = 0;
		case 2:
			red = 25;
			green = 180;
			blue = 255;
		case 3:
			red = 255;
			green = 0;
			blue = 0;
		case 4:
			red = 255;
			green = 0;
			blue = 0;
		case 5:
			red = 255;
			green = 0;
			blue = 0;
		case 6:
			red = 255;
			green = 0;
			blue = 0;
		case 7:
			red = 255;
			green = 0;
			blue = 0;
	}
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(red, green, blue), 1.0f, 0);

	d3dDevice->BeginScene();

	spritebrush->Begin(D3DXSPRITE_ALPHABLEND);



	spritebrush->End();

	d3dDevice->EndScene();

	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void bagscene() {
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(red, green, blue), 1.0f, 0);

	d3dDevice->BeginScene();

	spritebrush->Begin(D3DXSPRITE_ALPHABLEND);



	spritebrush->End();

	d3dDevice->EndScene();

	d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void input() {

	//	Acquire the device.
	dInputKeyboardDevice->Acquire();
	dInputMouseDevice->Acquire();
	//	Get immediate Keyboard Data.
	dInputKeyboardDevice->GetDeviceState(256, dikeys);
	dInputMouseDevice->GetDeviceState(sizeof(DIMOUSESTATE), &mousestate);

}

bool rectcollision(RECT a, RECT b) {
	if (a.bottom < b.top) return false;
	if (a.top > b.bottom) return false;
	if (a.right < b.left) return false;
	if (a.left > b.right) return false;

	return true;
}

void update() {
	int frame2update = frametimer.FramesToUpdate();
	for (int i = 0; i< frame2update; i++) {
		globalframe++;
		angle += 0.001;
		xangle += 0.01;

		//cout << drawtb1.getframe() << endl;
		drawtb1.setframe(drawtb1.getframe() + 1);
		if (drawtb1.getframe() >= 2) {
			drawtb1.setframe(0);
			cout << drawtb1.getframe() << endl;
		}
		//cout << drawtb1.getframe() << endl;
	
		drawtb2.setframe(drawtb2.getframe() + 1);
		if (drawtb2.getframe() >= 2) {
			drawtb2.setframe(0);
		}

	if (dikeys[DIK_UP] & 0x80)
	{
		std::cout << "UP" << std::endl;
	}

	drawmlt.calculateframe(globalframe,4);

	if (dikeys[DIK_W] & 0x80) {
		positionmlt.y--;

		drawmlt.setframe(drawmlt.getframe() + 1);
		if (drawmlt.getframe() < 12 || drawmlt.getframe() > 15) {
			drawmlt.setframe(12);
		}
		
	}
	if (dikeys[DIK_S] & 0x80) {
	positionmlt.y ++;

	drawmlt.setframe(drawmlt.getframe() + 1);
	if (drawmlt.getframe() > 3) {
		drawmlt.setframe(0);
	}
}

	 if (dikeys[DIK_A] & 0x80) {
		positionmlt.x --;

		drawmlt.setframe(drawmlt.getframe() + 1);
		if (drawmlt.getframe() > 7) {
			drawmlt.setframe(4);
		}
	}

	 if (dikeys[DIK_D] & 0x80) {
		positionmlt.x ++;

		drawmlt.setframe(drawmlt.getframe() + 1);
		if (drawmlt.getframe() > 11) {
			drawmlt.setframe(8);
		}
	}
	 if (dikeys[DIK_LEFT] & 0x80) {
		 ball1angle += 0.01f;
	 }
	 if (dikeys[DIK_RIGHT] & 0x80) {
		 ball1angle2 += 0.01f;
	 }

	}
	
	if (rectcollision(collisionrectmlt,collision2)) {
		//cout << "Collision" << endl;
	}

	mousep.x += mousestate.lX;
	mousep.y += mousestate.lY;
	//cout << "X: " << mousep.x << "Y: " << mousep.y << endl;
}


int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	
	Game runapp;
	runapp.rungame(hInstance);
	
	return 0;
}
//--------------------------------------------------------------------