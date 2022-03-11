#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "resource.h"

HINSTANCE GLOBAL_hInstance;

LRESULT CALLBACK WndProcInicioSesion(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProcVentanaPrincipal(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    GLOBAL_hInstance = hInstance;
    HWND hWndInicioSesion = CreateDialogW(
        hInstance,
        MAKEINTRESOURCE(IDD_INICIO_SESION),
        NULL,
        WndProcInicioSesion
    );

    if (hWndInicioSesion == NULL)
    {
        MessageBox(NULL, L"Ocurrio un error al crear el dialogo", L"=(", MB_OK | MB_ICONASTERISK);
        return 0;
    }

    ShowWindow(hWndInicioSesion, SW_SHOWNORMAL);
    


    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

LRESULT CALLBACK WndProcInicioSesion(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }break;
    case WM_COMMAND: {
        if (wParam == IDBTN_INICIAR_SESION)
        {
            HWND hWndVentanaPrincipal = CreateDialogW(
                GLOBAL_hInstance,
                MAKEINTRESOURCE(IDD_VENTANA_PRINCIPAL),
                hwnd,
                WndProcVentanaPrincipal
            );
            ShowWindow(hWndVentanaPrincipal, SW_SHOWNORMAL);
        }
    }break;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK WndProcVentanaPrincipal(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}