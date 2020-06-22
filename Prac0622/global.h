#pragma once
#include <d3dx9.h>
#include "texture_manager.h"
#include "input_manager.h"

#include "player.h"

extern LPDIRECT3D9             g_pD3D;
extern LPDIRECT3DDEVICE9       g_pd3dDevice;
extern TextureManager textureManager;
extern InputManager inputManager;

extern ID3DXFont* g_pFont;

extern Player player;

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480