#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

class Window
{

private:
	WNDCLASS wndClass;
	MSG msg;
	HWND g_hWnd = NULL;
	int windowwidth = 1920;
	int windowheight = 1080;

public:
	static Window& getInstance() {
		static Window instance;
		return instance;
	}
	void createwindow();
	bool runningwindow();
	void closewindow(HINSTANCE hInstance);
	int getwindowheight() {
		return windowheight;
	}
	int getwindowwidth() {
		return windowwidth;
	}
	HWND& getg_hwnd() {
		return g_hWnd;
	}
	
	static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static void fullscreen(HWND hWnd);
};

