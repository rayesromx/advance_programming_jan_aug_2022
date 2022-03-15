#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "resource.h"

HINSTANCE GlobalAppHInstance;

bool exitProgram = false;

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
    /* Este evento remueve el dialog de la pantalla 
    * Sent when a window is being destroyed. It is sent to the window procedure of the window being destroyed 
      after the window is removed from the screen.
      https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-destroy
    * */
    case WM_DESTROY:
        if (exitProgram) {
            PostQuitMessage(16);
        }
        return 0;

    /*Codigo para manejar eventos de entrada
    * Sent when the user selects a command item from a menu, when a control sends a notification message to its parent window, 
    * or when an accelerator keystroke is translated.
    * https://docs.microsoft.com/en-us/windows/win32/menurc/wm-command
    * */
    case WM_COMMAND: {
        /*
          wParam
            The LOWORD contains the button's control identifier. The HIWORD specifies the notification code.
            https://docs.microsoft.com/en-us/windows/win32/controls/bn-clicked
          lParam
            A handle to the button.
        */
        switch (LOWORD(wParam))
        {
        case IDBTN_LOGIN_SALIR: {
            //freeMemoryUser();
            exitProgram = true;
            DestroyWindow(hwnd);
        }break;
        }
    }break;
    /*Este evento se dispara cuando le picamos al boton X para cerrar
    * Sent as a signal that a window or an application should terminate. 
    * https://docs.microsoft.com/en-us/windows/win32/winmsg/wm-close
    */
    case WM_CLOSE:
        
        break;
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