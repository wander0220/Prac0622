#include "framework.h"
#include "Prac0622.h"

#include <Windows.h>

#include "global.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                
WCHAR szTitle[MAX_LOADSTRING];                
WCHAR szWindowClass[MAX_LOADSTRING];           

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

LPDIRECT3D9             g_pD3D;
LPDIRECT3DDEVICE9       g_pd3dDevice;

TextureManager textureManager;
InputManager inputManager;

bool GameExit = TRUE;

Player player;

ID3DXFont* g_pFont;

HRESULT InitD3D(HWND hWnd)
{
    if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
        return E_FAIL;
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = TRUE;

    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
        D3DCREATE_SOFTWARE_VERTEXPROCESSING,
        &d3dpp, &g_pd3dDevice)))
    {
        return E_FAIL;
    }
    g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
    g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

    return S_OK;
}
void InitMyStuff() {
    
    D3DXCreateFont(g_pd3dDevice, -12, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
        L"System", &g_pFont);

    textureManager.LoadTexture(L"player/player1.png", 200);
    /*D3DXCreateSprite(g_pd3dDevice, &g_pTextSprite);
    D3DXCreateTextureFromFile(g_pd3dDevice, L"banana.bmp", &g_pTexture);*/
}
void EngineUpdate() {
    if (inputManager.keyBuffer[VK_ESCAPE] == 1) {
        GameExit = false;
    }
    player.Update();
    inputManager.Update();
}
VOID EngineRender()
{
    RECT rc;
    rc.left = 0;
    rc.top = 0;
    rc.right = 100;
    rc.bottom = 100;


    g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
        D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

    if (SUCCEEDED(g_pd3dDevice->BeginScene()))
    {
        /*TextureElements* elements = textureManager.GetTexture(200);

        elements->sprite->Begin(D3DXSPRITE_ALPHABLEND);

        RECT rec;
        rec.left = 0;
        rec.top = 0;
        rec.right = 64;
        rec.bottom = 64;

        D3DXVECTOR3 pos(0, 0, 0);

        elements->sprite->Draw(elements->texture, &rec
            , nullptr,nullptr, D3DCOLOR_XRGB(255, 255, 255));
        elements->sprite->End();*/

        RECT rec;
        rec.left = 40;
        rec.top = 40;
        rec.right = 100;
        rec.bottom = 100;

        WCHAR buffer[128];
        int i = 23;
        swprintf_s(buffer, L"김수현 : %d", i);
        
        g_pFont->DrawText(NULL,
            buffer, -1, &rec,
            DT_NOCLIP, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


        player.Render();

        g_pd3dDevice->EndScene();
    }
    g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PRAC0622, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PRAC0622));

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT && GameExit)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            EngineUpdate();
            EngineRender();
        }
    }

    return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PRAC0622));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName = nullptr; //MAKEINTRESOURCEW(IDC_PRAC0622);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, WINDOW_WIDTH, WINDOW_HEIGHT, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   InitD3D(hWnd);
   InitMyStuff();
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
int a;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_KEYDOWN:
        a = 10;
        inputManager.keyBuffer[wParam] = 1;
        break;
    case WM_KEYUP:
        inputManager.keyBuffer[wParam] = 0;
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}