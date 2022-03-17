#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "resource.h"
#include <string.h>
#include <string>

using namespace std;

HINSTANCE GlobalhInstance;
string Globalusuario;

INT_PTR CALLBACK fDialogoInicioSesion(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fDialogoVentanaPrincipal(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

wchar_t* getTextFromComponent(HWND hComponent);
string wcharToStr(wchar_t* str);
const wchar_t* strToWChar(string str);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    GlobalhInstance = hInstance;
    //H = HANDLER
    //WND = WINDOW
    //handler o manejador del dialogo
    HWND handlerDialogoInicioSesion =
        CreateDialogW(
            GlobalhInstance,//la instancia es el identificador que asigna windows a nuestra aplicacion
            MAKEINTRESOURCE(IDD_INICIOSESION),
            NULL,
            fDialogoInicioSesion
        );

    
    ShowWindow(handlerDialogoInicioSesion, SW_SHOW);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

INT_PTR CALLBACK fDialogoInicioSesion(
    HWND hwnd, //handler o manejador del dialogo
    UINT uMsg, //mensaje o evento que esta escuchando la funcion
    WPARAM wParam, //contiene informacion adicional del mensaje
    LPARAM lParam  //contiene informacion adicional del mensaje
)
{
    //DEFINIR QUE VA A HACER MI DIALOG DE INICIO DE SESION
    switch (uMsg)
    {
    //Este evento se dispara cuando interactuamos con cualquier componente
    case WM_COMMAND: {
        //este switch determinamos con que componente se esta interactuando
        switch (LOWORD(wParam))
        {
        case IDBTN_INICIARSESION:
        {
            HWND handlerUsuario = GetDlgItem(hwnd, IDTXT_USUARIO);
            wchar_t* wusario = getTextFromComponent(handlerUsuario);
            Globalusuario = wcharToStr(wusario);

            HWND handlerDialogoVentanaPrincipal =
                CreateDialogW(
                    GlobalhInstance,//la instancia es el identificador que asigna windows a nuestra aplicacion
                    MAKEINTRESOURCE(IDD_VENTANAPRINCIPAL),
                    NULL,
                    fDialogoVentanaPrincipal
                );

            ShowWindow(handlerDialogoVentanaPrincipal, SW_SHOW);
            DestroyWindow(hwnd);
        }
        break;
        case IDBTN_SALIR:
        {
            int respuesta = MessageBox(hwnd,
                L"Estas seguro que quieres cerrar el app?",
                L"Antes de irte....",
                MB_OKCANCEL | MB_ICONEXCLAMATION);
            if (respuesta == IDOK)
            {
                DestroyWindow(hwnd);
                PostQuitMessage(0);//cierra completamente el app
            }
        }
        break;
        }
    }break;
    }
    return FALSE;
}

INT_PTR CALLBACK fDialogoVentanaPrincipal(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
    {
       /* HWND handlerLabel = GetDlgItem(hwnd, IDLBL_TEXTO);

        wstring widestr = wstring(Globalusuario.begin(), Globalusuario.end());
        const wchar_t* widecstr = widestr.c_str();*/

        //const wchar_t* usuario = strToWChar(Globalusuario);

        ///SetWindowText(handlerLabel, widecstr);
    }
    break;
    }
    

    return FALSE;
}

wchar_t* getTextFromComponent(HWND hComponent) {
    int length = GetWindowTextLength(hComponent);
    if (length < 1)
        return NULL;
    wchar_t* textoLeidoDelComponente = new wchar_t[++length];
    GetWindowText(hComponent, textoLeidoDelComponente, length);
    return textoLeidoDelComponente;
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