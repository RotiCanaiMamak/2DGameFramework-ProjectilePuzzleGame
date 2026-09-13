#include "DirectInput.h"

void DirectInput::createdi() {
	HWND& hwnd = Window::getInstance().getg_hwnd();

	//	Create the Direct Input object.
	HRESULT hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);
	if (FAILED(hr)) {
		MessageBox(hwnd, "DirectInput8Create failed", "Error", MB_OK);
		return;
	}

	//	Create the keyboard device.
	hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);
	if (FAILED(hr)) {
		MessageBox(hwnd, "Failed to create keyboard device", "Error", MB_OK);
		return;
	}

	hr = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);
	if (FAILED(hr)) {
		MessageBox(hwnd, "Failed to create mouse device", "Error", MB_OK);
		return;
	}

	//	Set the input data format.
	hr = dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)) {
		MessageBox(hwnd, "Failed to set keyboard data format", "Error", MB_OK);
		return;
	}

	hr = dInputMouseDevice->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr)) {
		MessageBox(hwnd, "Failed to set mouse data format", "Error", MB_OK);
		return;
	}

	//	Set the cooperative level.
	//	To Do:
	//	Try with different combination.
	hr = dInputKeyboardDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr)) {
		MessageBox(hwnd, "Failed to set keyboard cooperative level", "Error", MB_OK);
		return;
	}

	hr = dInputMouseDevice->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr)) {
		MessageBox(hwnd, "Failed to set mouse cooperative level", "Error", MB_OK);
		return;
	}
}

void DirectInput::cleandi() {
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
