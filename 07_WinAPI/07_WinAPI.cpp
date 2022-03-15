#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "resource.h"

HINSTANCE GlobalAppHInstance;

LRESULT CALLBACK DefaultWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK fLoginProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    GlobalAppHInstance = hInstance;

    //Creamos una dialogo a partir de la plantilla IDD_LOGIN
    HWND handlerLoginWindow = CreateDialogW(
        GlobalAppHInstance,//La instancia de nuestra aplicacion
        MAKEINTRESOURCE(IDD_LOGIN),//El ID del dialogo que vamos a crear
        NULL, //Como esta es la primera ventana, no tiene una ventana padre
        fLoginProc //La funcion Window Procedure asociada a este dialogo
    );

    //validamos que no haya habido errores
    if (handlerLoginWindow == NULL)
    {
        MessageBox(NULL,
            L"Hubo un error al crear la aplicacion. Contacte al administrador o soporte.",
            L"ERROR FATAL", 
            MB_OK | MB_ICONERROR
            );
        return 0;
    }

    //Mostramos la ventana y listo, hasta aqui llega todo el codigo interesante del main
    //en este ejercicio
    ShowWindow(handlerLoginWindow, SW_NORMAL);

    // Recuerden que el message loop siempre debe de estar

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK fLoginProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;


        return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK DefaultWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}