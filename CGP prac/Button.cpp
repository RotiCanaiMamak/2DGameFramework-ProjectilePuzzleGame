#include "Button.h"

bool Button::onbutton(float x, float y) {
	return (x >= rect.left && x <= rect.right && y >= rect.top && y <= rect.bottom);
}