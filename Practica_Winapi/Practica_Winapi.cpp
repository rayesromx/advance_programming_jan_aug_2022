#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "resource.h"
#include <string>

using namespace std;

HINSTANCE GlobalhInstance;

string usuario; 


wchar_t* getTextFromComponent(HWND hComponent);
string wcharToStr(wchar_t* str);

const wchar_t* strToWchar(string str)
{
    std::wstring widestr = std::wstring(str.begin(), str.end());
    const wchar_t* widecstr = widestr.c_str();
    return widecstr;
}

INT_PTR CALLBACK fInicioSesion(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
INT_PTR CALLBACK fMenuPrincipal(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    GlobalhInstance = hInstance;
    //codigo para crear un dialogo a partir de la plantilla
    HWND handlerVentanaInicioSesion =
        CreateDialogW(
            GlobalhInstance,//instancia de la aplicacion
            MAKEINTRESOURCE(IDD_INICIOSESION),//Dialogo que se va a crear
            NULL,
            fInicioSesion
        );

    //Validar que el dialogo se no creo con exito
    if (handlerVentanaInicioSesion == NULL)
    {
        MessageBox(NULL,
            L"Ocurrio un error al crear la ventana",
            L"ERROR FATAL",
            MB_OK | MB_ICONERROR);
        return 0;
    }

    ShowWindow(handlerVentanaInicioSesion, SW_SHOW);

    //Message loop
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

INT_PTR CALLBACK fInicioSesion(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
        //evento que se dispara con la interaccion de componentes(botones, etc)
    case WM_COMMAND:
    {
        switch (LOWORD(wparam))
        {
        case IDBTN_INICIOSESION_REGISTRAR:
        {
            MessageBox(NULL,
                L"REGISTRAR",
                L"ERROR FATAL",
                MB_OK | MB_ICONERROR);
        }
        break;
        case IDBTN_INICIOSESION_INICIARSESION:
        {
            HWND hTxtLoginUserName = GetDlgItem(hwnd, IDTXT_INICIOSESION_USUARIO);

            wchar_t* wusario = getTextFromComponent(hTxtLoginUserName);
            usuario = wcharToStr(wusario);

            HWND handlerMenuPrincipal =
                CreateDialogW(
                    GlobalhInstance,//instancia de la aplicacion
                    MAKEINTRESOURCE(IDD_MENUPRINCIPAL),//Dialogo que se va a crear
                    NULL,
                    fMenuPrincipal
                );
            ShowWindow(handlerMenuPrincipal, SW_SHOW);
            ShowWindow(hwnd, SW_HIDE);
            
        }
        break;
        case IDBTN_INICIOSESION_SALIR:
        {
            DestroyWindow(hwnd); // destruir la ventana
            PostQuitMessage(0); // destruir la aplicacion
        }
        break;

        }
    }
    break;
    }
    return FALSE;
}

INT_PTR CALLBACK fMenuPrincipal(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
    case WM_INITDIALOG:
    {
        HWND handlerTxtMensaje = GetDlgItem(hwnd, IDTXT_MENSAJE);
        HWND handlerLblMensaje = GetDlgItem(hwnd, IDLBL_MENSAJE);
        const wchar_t* temp = strToWchar(usuario);
        SetWindowText(handlerTxtMensaje, temp);
        SetWindowText(handlerLblMensaje, temp);
    }
    break;

    }

    return FALSE;
}


wchar_t* getTextFromComponent(HWND hComponent)
{
    int length = GetWindowTextLength(hComponent);
    if (length < 1)
        return NULL;
    wchar_t* wct = new wchar_t[++length];
    GetWindowText(hComponent, wct, length);
    return wct;
}

string wcharToStr(wchar_t* str)
{
    wstring ws(str);
    string sText(ws.begin(), ws.end());
    return sText;
}