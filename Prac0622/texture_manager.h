#pragma once
#include <d3dx9core.h>
#include <vector>

using namespace std;

class TextureElements {
public:
	int id;
	LPDIRECT3DTEXTURE9     texture;
	ID3DXSprite* sprite;
};
class TextureManager
{
public:
	vector<TextureElements*> elements;
	void LoadTexture(const TCHAR* name, int id);
	TextureElements* GetTexture(int id);
};

