#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "resource.h"
#include <string>
using namespace std;

HINSTANCE GlobalAppHInstance;

bool exitProgram = false;

INT_PTR CALLBACK DefaultWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fLoginProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fOtroProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

wchar_t* getTextFromComponent(HWND hComponent);
string wcharToStr(wchar_t* str);
const wchar_t* strToWChar(string str);

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
    ShowWindow(handlerLoginWindow, SW_SHOW);
    UpdateWindow(handlerLoginWindow);

    // Recuerden que el message loop siempre debe de estar

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

INT_PTR CALLBACK fLoginProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
        case IDBTN_LOGIN_INICIARSESION:
        {
            HWND hTxtLoginUserName = GetDlgItem(hwnd, IDTXT_LOGIN_USUARIO);

            wchar_t* wusario = getTextFromComponent(hTxtLoginUserName);
            string usuario = wcharToStr(wusario);
            int respuesta = MessageBox(hwnd, wusario, L"ALERT", MB_OKCANCEL);
            if (respuesta != IDOK)
                break;

            HWND handlerOtro = CreateDialogW(GlobalAppHInstance, MAKEINTRESOURCE(IDD_OTRO), NULL, fOtroProc);
            ShowWindow(handlerOtro, SW_SHOW);
            DestroyWindow(hwnd);
        }break;
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
    //Los dialogos no siguen las mismas reglas que las ventanas en terminos de sus funciones Windos/Dialog Procedure
    //por lo tanto simplemente retornamos FALSE en nuestros Dialog Procedures
    //https://docs.microsoft.com/en-us/windows/win32/api/winuser/nc-winuser-dlgproc?redirectedfrom=MSDN
    return FALSE;
}

bool estaHabilitado = true;
INT_PTR CALLBACK fOtroProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    string lista_de_nombres[10];
    lista_de_nombres[0] = "Ray";
    lista_de_nombres[1] = "Angy";
    lista_de_nombres[2] = "Rober";
    lista_de_nombres[3] = "Angel";
    lista_de_nombres[4] = "Jose";
    lista_de_nombres[5] = "Alicia";
    lista_de_nombres[6] = "Lili";
    lista_de_nombres[7] = "Juan";
    lista_de_nombres[8] = "Maleny";
    lista_de_nombres[9] = "Antonio";

    switch (uMsg)
    {
    case WM_INITDIALOG: {
        

        HWND handlerListado = GetDlgItem(hwnd, IDLB_LISTADO);
        
        for (int i = 0; i < 9; i++)
        {
            wstring ws = wstring(lista_de_nombres[i].begin(), lista_de_nombres[i].end());
            LPARAM item = reinterpret_cast<LPARAM>(ws.c_str());
            int indice = SendMessage(handlerListado, LB_ADDSTRING, 0, item);
            SendMessage(handlerListado, LB_SETITEMDATA, indice, i);
        }


    }break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_COMMAND: {
        switch (LOWORD(wParam))
        {
        case IDBTN_CAMBIAR: {
            HWND handlerTxtOtro = GetDlgItem(hwnd, IDTXT_OTRO);
            estaHabilitado = !estaHabilitado;
            EnableWindow(handlerTxtOtro, estaHabilitado);
        }break;
        case IDBTN_PONERTEXTO: {
            HWND handlerTxtOtro = GetDlgItem(hwnd, IDTXT_OTRO);
            SetWindowText(handlerTxtOtro, L"Hello, World!!!");
        }break;
        case IDBTN_LIMPIAR: {
            HWND handlerTxtOtro = GetDlgItem(hwnd, IDTXT_OTRO);
            SetWindowText(handlerTxtOtro, L"");
        }break;
        case IDLB_LISTADO:
        {
            if (HIWORD(wParam) == LBN_SELCHANGE)
            {
                int lbIndex = SendDlgItemMessage(hwnd, IDLB_LISTADO, LB_GETCURSEL, NULL, NULL);
                int indiceDeArreglo = SendDlgItemMessage(hwnd, IDLB_LISTADO, LB_GETITEMDATA, lbIndex, NULL);

                wstring ws = wstring(lista_de_nombres[indiceDeArreglo].begin(), lista_de_nombres[indiceDeArreglo].end());
                MessageBox(hwnd, ws.c_str(), L"Elemento seleccionado", MB_OK | MB_ICONINFORMATION);
            }
        }break;
        }
    }break;
    }
    return FALSE;
}


INT_PTR CALLBACK DefaultWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

wchar_t* getTextFromComponent(HWND hComponent) {
    int length = GetWindowTextLength(hComponent);
    if (length < 1)
        return NULL;
    wchar_t* wct = new wchar_t[++length];
    GetWindowText(hComponent, wct, length);
    return wct;
   /* wstring ws(wct);
    string sText(ws.begin(), ws.end());
    return sText;*/
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