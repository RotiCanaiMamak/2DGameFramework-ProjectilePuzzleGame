#pragma once
#include <dinput.h>
#include "Window.h"

class DirectInput
{
private:
	
	LPDIRECTINPUTDEVICE8  dInputKeyboardDevice;		//	Direct Input keyboard device.
	LPDIRECTINPUTDEVICE8  dInputMouseDevice;		//	Direct Input mouse device.
	LPDIRECTINPUT8 dInput;							//	Direct Input object.

public:
	static DirectInput& getInstance() {
		static DirectInput instance;
		return instance;
	}

	void createdi();
	void cleandi();
	
	LPDIRECTINPUTDEVICE8  getkeyboard() {
		return dInputKeyboardDevice;
	}

	LPDIRECTINPUTDEVICE8  getmouse() {
		return dInputMouseDevice;
	}

};

