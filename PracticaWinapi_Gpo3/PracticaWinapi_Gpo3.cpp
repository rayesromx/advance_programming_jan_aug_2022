#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "resource.h"
#include <string>
using namespace std;

HINSTANCE GlobalhInstance;
wchar_t* w_usuario;
bool botonHabilitado = true;

//prototipo
INT_PTR CALLBACK fDialogoInicioDeSesion(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fDialogoVentanaPrincipal(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


wchar_t* getTextFromComponent(HWND hComponent) {
    int length = GetWindowTextLength(hComponent);
    wchar_t* texto = new wchar_t[++length];
    GetWindowText(hComponent, texto, length);
    return texto;
}

string wcharToStr(wchar_t* str)
{
    wstring ws(str);
    string sText(ws.begin(), ws.end());
    return sText;
}

const wchar_t* strToWChar(string str)
{
    wstring widestr = wstring(str.begin(), str.end());
    const wchar_t* widecstr = widestr.c_str();
    return widecstr;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    GlobalhInstance = hInstance;
    //H => handler
    //WND => window
    //manejador de la ventana
    HWND handlerDialogoInicioDeSesion = CreateDialogW(
        hInstance,
        MAKEINTRESOURCE(IDD_INICIODESESION),
        NULL,
        fDialogoInicioDeSesion
    );

    if (handlerDialogoInicioDeSesion == NULL)
    {
        MessageBox(
            NULL,
            L"Ocurrio un error al crear la aplicacion. Contacta a tu administrador",
            L"ERROR FATAL",
            MB_OK | MB_ICONERROR
        );
        return 0;
    }

    ShowWindow(handlerDialogoInicioDeSesion, SW_SHOW);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

INT_PTR CALLBACK fDialogoInicioDeSesion(
    HWND hwnd, //handler de la ventana
    UINT uMsg, //evento o mensaje que se ha disparado
    WPARAM wParam,//contienen informacion adicional del mensaje 
    LPARAM lParam //contienen informacion adicional del mensaje
)
{
    switch (uMsg)
    {
        //este evento se dispara cuando interactuamos con cualquier
        //componente
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDBTN_SALIR:
        {
            PostQuitMessage(0);//WM_QUIT
            DestroyWindow(hwnd);
        }
        break;
        case IDBTN_INICIARSESION:
        {
            HWND handlerTXTUsuario = GetDlgItem(hwnd, IDTXT_Usuario);

            w_usuario = getTextFromComponent(handlerTXTUsuario);

            HWND handlerDialogoVentanaInicial = 
                CreateDialogW(
                    GlobalhInstance,
                MAKEINTRESOURCE(IDD_VENTANAPRINCIPAL),
                NULL,
                fDialogoVentanaPrincipal
            );

            ShowWindow(handlerDialogoVentanaInicial, SW_SHOW);
            DestroyWindow(hwnd);
        }
        break;

        }
    
    }
    break;

    }
    return FALSE;
}

INT_PTR CALLBACK fDialogoVentanaPrincipal(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
    {
        HWND handlerLabelPrueba = GetDlgItem(hwnd, IDLBL_PRUEBA);
        SetWindowText(handlerLabelPrueba, w_usuario);
    }
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDBTN_LIMPIAR:
        {
            HWND handlerTexto = GetDlgItem(hwnd, IDTXT_DATO);
            SetWindowText(handlerTexto, L"");
        }
        break;
        case IDBTN_ESTABLECERTEXTO:
        {
            HWND handlerTexto = GetDlgItem(hwnd, IDTXT_DATO);
            SetWindowText(handlerTexto, L"RAY");
        }
        break;
        case IDBTN_HABILITADOR:
        {
            HWND handlerBoton = GetDlgItem(hwnd, IDBTN_HABILITADOR);
            HWND handlerTexto = GetDlgItem(hwnd, IDTXT_DATO);
            //wchar_t* textoBtn = getTextFromComponent(handlerBoton);
            if (botonHabilitado)
            {
                SetWindowText(handlerBoton, L"Deshabilitado");
                
            }
            else
            {
                SetWindowText(handlerBoton, L"Habilitado");
            }
            EnableWindow(handlerTexto, botonHabilitado);
            botonHabilitado = !botonHabilitado;

        }
        break;
        }
    }
    break;
    }
   

    return FALSE;
}