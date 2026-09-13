#include "LineBrush.h"

void LineBrush::createline() {
	DirectX& dx = DirectX::getInstance();

	HRESULT hr = D3DXCreateLine(dx.getdevice(), &linebrush);
}

void LineBrush::drawline(Line drawedline) {
	linebrush->SetWidth(drawedline.getwidth());
	linebrush->Draw(drawedline.getvertices(), 2, drawedline.getlinecolor());
}

void LineBrush::cleanline() {
	linebrush->Release();
	linebrush = NULL;
}