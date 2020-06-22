#include "texture_manager.h"
#include "global.h"
void TextureManager::LoadTexture(const TCHAR* name, int id) 
{
	int a = 10;
	TextureElements* newTexture = new TextureElements();
	newTexture->id = id;

	D3DXCreateSprite(g_pd3dDevice, &newTexture->sprite);
	D3DXCreateTextureFromFile(g_pd3dDevice,name, &newTexture->texture);

	elements.push_back(newTexture);

}
TextureElements* TextureManager::GetTexture(int id) 
{
	for (int i = 0; i < elements.size(); i++) {
		if (elements[i]->id == id) {
			return elements[i];
		}
	}
	return nullptr;

}
