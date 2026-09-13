#include "SpriteBrush.h"
#include "Sprite.h"

void SpriteBrush::createsb() {
	DirectX& dx = DirectX::getInstance();

	//	Create sprite. Study the documentation. 
	HRESULT hr = D3DXCreateSprite(dx.getdevice(), &spritebrush);

}

LPDIRECT3DTEXTURE9 SpriteBrush::LoadTexture(const string& filename,D3DCOLOR colorkey){
	DirectX& dx = DirectX::getInstance();

	//string assetspic = "assets\\newbg1.png";
	//	Create texture. Study the documentation.

	if (FAILED(D3DXCreateTextureFromFileEx(dx.getdevice(), filename.c_str(), D3DX_DEFAULT, D3DX_DEFAULT,
		D3DX_DEFAULT, NULL, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, colorkey,
		NULL, NULL, &texture))) {
		string errormsg = "No " + filename;
		MessageBox(NULL, errormsg.c_str(), "ERROR", MB_OK);
	}

	/*if (FAILED(D3DXCreateTextureFromFile(d3dDevice, "assets\\newbg1.png", &texture))) {
		MessageBox(NULL, "No texture1!", "ERROR", MB_OK);
	}*/
	return texture;
}

void SpriteBrush::cleansb() {
	spritebrush->Release();
	spritebrush = NULL;

	texture->Release();
	texture = NULL;
}

void SpriteBrush::drawsprite(Sprite spritedrawed) {
	RECT spriterect = spritedrawed.getrectbox();
	spritebrush->Draw(spritedrawed.gettexture(), &spriterect, NULL, &spritedrawed.getposition(), D3DCOLOR_XRGB(255, 255, 255));
}

void SpriteBrush::settranform(D3DXMATRIX* transformatrix) {
	spritebrush->SetTransform(transformatrix);
}

void SpriteBrush::drawtexture(LPDIRECT3DTEXTURE9 txture, D3DXVECTOR3& pos) {
	spritebrush->Draw(txture, NULL, NULL, &pos, D3DCOLOR_XRGB(255, 255, 255));
}
