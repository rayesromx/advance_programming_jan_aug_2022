#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h> //con mayor y menor que se busca el header file en la carpeta de librerias de c++
#include "resource.h" // con comillas dobles se busca el arch de cabecera en la carpeta del proyecto
#include <string>

using namespace std;

HINSTANCE GlobalhInstance;


struct Pokemon {
    string name;
    string type;
    int number;

    Pokemon* next;
    Pokemon* previous;
};

Pokemon* PokeList;


INT_PTR CALLBACK fDlgPokeApp(HWND hDlgParent, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fDlgPokeAdd(HWND hDlgParent, UINT uMsg, WPARAM wParam, LPARAM lParam);

string getTextFromComponent(HWND hDlgParent, int idComponent);

void setTextToComponent(HWND hComponent, string text)
{
    wstring widestr = wstring(text.begin(), text.end());
    LPCWSTR componentText = widestr.c_str();
    SetWindowText(hComponent, componentText);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    PokeList = NULL;
    GlobalhInstance = hInstance;
    //Handler WiNDow
    HWND hDlgPokeApp = CreateDialogW(
        GlobalhInstance,
        MAKEINTRESOURCE(IDD_POKEAPP),
       NULL,
        fDlgPokeApp
    );
    // Run the message loop.

    ShowWindow(hDlgPokeApp,SW_SHOW);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}


INT_PTR CALLBACK fDlgPokeApp(HWND hDlgParent, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
    {
        if (PokeList == NULL)
            break;

        HWND lbPokeList = GetDlgItem(hDlgParent, IDLB_POKELIST);

        Pokemon* aux = PokeList;

        while (aux != NULL)
        {
            string str = aux->name;
            wstring ws = wstring(str.begin(), str.end());
            const wchar_t* wc = ws.c_str();
            int index = SendMessage(lbPokeList, LB_ADDSTRING, 0, (LPARAM)(wc));
            SendMessage(lbPokeList, LB_SETITEMDATA, index, (LPARAM)aux);
            aux = aux->next;
        }
    }
    break;

    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDLB_POKELIST:
        {
            switch (HIWORD(wParam))
            {
            case LBN_SELCHANGE:
            {
            
                int index = SendDlgItemMessage(hDlgParent, IDLB_POKELIST, LB_GETCURSEL, NULL, NULL);
                Pokemon* selectedPokemon = (Pokemon*)SendDlgItemMessage(hDlgParent, IDLB_POKELIST, LB_GETITEMDATA, index, NULL);

                HWND id_EDIT1 = GetDlgItem(hDlgParent, IDC_EDIT1);
                HWND id_EDIT2 = GetDlgItem(hDlgParent, IDC_EDIT2);
                HWND id_EDIT3 = GetDlgItem(hDlgParent, IDC_EDIT3);

                setTextToComponent(id_EDIT1, selectedPokemon->name);
                setTextToComponent(id_EDIT2, selectedPokemon->type);
                setTextToComponent(id_EDIT3, to_string(selectedPokemon->number));

            }
            break;
            }
            
        }
        break;

        case IDBTN_ADD:
        {
           // MessageBox(hDlgParent, L"asdasd", L"asdasd", MB_OK);

            HWND hDlgPokeAdd = CreateDialogW(
                GlobalhInstance,
                MAKEINTRESOURCE(IDD_ADDNEWPKMN),
                NULL,
                fDlgPokeAdd
            );
            // Run the message loop.

            ShowWindow(hDlgPokeAdd, SW_SHOW);
            DestroyWindow(hDlgParent);
        }
        break;
        }
    }
    break;
    default:
        break;
    }
    return FALSE;
}

INT_PTR CALLBACK fDlgPokeAdd(HWND hDlgParent, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDOK:
        {
            string strName = getTextFromComponent(hDlgParent, IDTXT_PKMNNAME);
            string strType = getTextFromComponent(hDlgParent, IDTXT_PKMNTYPE);
            string strNumber = getTextFromComponent(hDlgParent, IDTXT_PKMNNUMBER);

            Pokemon* newPokemon = new Pokemon;
            newPokemon->name = strName;
            newPokemon->type = strType;
            newPokemon->number = atoi(strNumber.c_str());
            newPokemon->next = NULL;
            newPokemon->previous = NULL;


            if (PokeList == NULL)
            {
                PokeList = newPokemon;
            }
            else
            {
                Pokemon* lastPokemon = PokeList;
                while (lastPokemon->next != NULL)
                    lastPokemon = lastPokemon->next;

                lastPokemon->next = newPokemon;
                newPokemon->previous = lastPokemon;
            }


            HWND hDlgPokeApp = CreateDialogW(
                GlobalhInstance,
                MAKEINTRESOURCE(IDD_POKEAPP),
                NULL,
                fDlgPokeApp
            );
            // Run the message loop.
            ShowWindow(hDlgPokeApp, SW_SHOW);
            DestroyWindow(hDlgParent);

        }break;

        case IDCANCEL:
        {
            HWND hDlgPokeApp = CreateDialogW(
                GlobalhInstance,
                MAKEINTRESOURCE(IDD_POKEAPP),
                NULL,
                fDlgPokeApp
            );
            // Run the message loop.
            ShowWindow(hDlgPokeApp, SW_SHOW);
            DestroyWindow(hDlgParent);
        }
        break;
        default:
            break;
        }
    }
    break;
    default:
        break;
    }

    return false;
}


string getTextFromComponent(HWND hDlgParent, int idComponent)
{
    HWND hText = GetDlgItem(hDlgParent, idComponent);
    wchar_t wText[50];
    GetWindowText(hText, wText, 50);

    wstring ws = wstring(wText);
    string str(ws.begin(), ws.end());

    return str;
}