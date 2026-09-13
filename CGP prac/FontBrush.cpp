#include "FontBrush.h"

void FontBrush::createfont() {
	DirectX& dx = DirectX::getInstance();

	HRESULT hr = D3DXCreateFont(dx.getdevice(), 45, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Times New Roman", &fontbrush);
}
void FontBrush::cleanfont() {
	for (auto& kv : fontCache) {
		if (kv.second)kv.second->Release();
	}
	fontCache.clear(); 

	fontbrush->Release();
	fontbrush = NULL;
}

LPD3DXFONT FontBrush::getfontbrush(Font fontdrawed) {
	DirectX& dx = DirectX::getInstance();

	//check if alr have same size and width , then no ned create a new one
	auto key = make_pair(fontdrawed.gettextsize(), fontdrawed.gettextwidth());
	if (fontCache.find(key) != fontCache.end()) {
		return fontCache[key];
	}

	//if not create new one
	LPD3DXFONT newFont = nullptr;
	HRESULT hr = D3DXCreateFont(dx.getdevice(), fontdrawed.gettextsize(), 0,fontdrawed.gettextwidth(), 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Times New Roman", &newfontbrush);
	
	if (SUCCEEDED(hr)) {
		fontCache[key] = newfontbrush;
		return newfontbrush;
	}

	return nullptr;
}

void FontBrush::drawfont(Font fontdrawed) {
	getfontbrush(fontdrawed)->DrawText(spritebrush.getspritebrush(), fontdrawed.gettextoutput().c_str(), -1, fontdrawed.gettextrectptr(), DT_LEFT | DT_TOP | DT_WORDBREAK , fontdrawed.getcolor());
}