#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h> //con mayor y menor que se busca el header file en la carpeta de librerias de c++
#include "resource.h" // con comillas dobles se busca el arch de cabecera en la carpeta del proyecto
#include <string>
#include "Pokemon.h"
#include "Utilerias.h"

using namespace std;

INT_PTR CALLBACK fDlgPokeApp(HWND hDlgParent, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fDlgPokeAdd(HWND hDlgParent, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    openPkmnFile();
    SetHInstance(hInstance);
    //Handler WiNDow
    HWND hDlgPokeApp = CreateAndShowDialog(IDD_POKEAPP, fDlgPokeApp);
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    savePkmnFile();
    return 0;
}

INT_PTR CALLBACK fDlgPokeApp(HWND hDlgParent, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
    {
        HMENU hmenu = LoadMenu(GetHInstance(), MAKEINTRESOURCE(IDR_MENU1));
        SetMenu(hDlgParent, hmenu);
        if (GetPokemonList() == NULL)
            break;
        HWND lbPokeList = GetDlgItem(hDlgParent, IDLB_POKELIST);
        Pokemon* aux = GetPokemonList();
        while (aux != NULL)
        {
            int index = SendMessage( lbPokeList, LB_ADDSTRING, 0, (LPARAM)(stringToWchar(aux->name)));
            SendMessage(lbPokeList, LB_SETITEMDATA, index, (LPARAM)aux);
            aux = aux->next;
        }
    }
    break;
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDMENU_BTN_ADD:
        {
            PostQuitMessage(0);
        }
        break;
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
            HWND hDlgPokeAdd = CreateAndShowDialog(IDD_ADDNEWPKMN, fDlgPokeAdd);
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

            Pokemon* newPokemon = CreateNewPokemon(strName, strType, strNumber);
            insertNewPokemon(newPokemon);

            HWND hDlgPokeApp = CreateAndShowDialog(IDD_POKEAPP, fDlgPokeApp);
            DestroyWindow(hDlgParent);

        }break;

        case IDCANCEL:
        {
            HWND hDlgPokeApp = CreateAndShowDialog(IDD_POKEAPP, fDlgPokeApp);
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