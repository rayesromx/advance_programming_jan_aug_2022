#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "resource.h"
#include <string>
using namespace std;


struct Pokemon
{
    string name;
    string type;
    int number;

    Pokemon* next;
    Pokemon* previous;
};

Pokemon* PokeList;

HINSTANCE GlobalhInstance;

string getTextFromComponent(HWND hParent, int idComponent);
void setTextToComponent(HWND hComponent, string text);

INT_PTR CALLBACK fDialogPokeApp(HWND handle, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fDialogPokeForm(HWND handle, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    GlobalhInstance = hInstance;
    PokeList = NULL;
    HWND hDialogPokeApp = CreateDialogW(
        GlobalhInstance,
        MAKEINTRESOURCE(IDD_POKEAPP),
        NULL,
        fDialogPokeApp
    );
  
    ShowWindow(hDialogPokeApp, SW_SHOW);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

INT_PTR CALLBACK fDialogPokeApp(HWND hDlgParent, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
    {
        HWND hTxtName = GetDlgItem(hDlgParent, IDTXT_PKMNNAME);
        EnableWindow(hTxtName, false);


        if (PokeList == NULL)
        {
            MessageBox(hDlgParent, L"EMPTY LIST", L"NO POKEMONS", MB_OK | MB_ICONEXCLAMATION);
        }
        else
        {
            HWND lbPokeList = GetDlgItem(hDlgParent, IDLB_PKMNLIST);
            
            Pokemon* aux = PokeList;
            while (aux != NULL)
            {
                wstring ws = wstring(aux->name.begin(), aux->name.end());
                const wchar_t* wc = ws.c_str();
                
                int listBoxIndex = SendMessage(lbPokeList, LB_ADDSTRING, 0, (LPARAM)wc);
                SendMessage(lbPokeList, LB_SETITEMDATA, listBoxIndex, (LPARAM)aux);
               
                aux = aux->next;
            }
        }
    }
    break;

    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDLB_PKMNLIST:
        {
            switch (HIWORD(wParam))
            {
            case LBN_SELCHANGE:
            {
                int index = SendDlgItemMessage(hDlgParent, IDLB_PKMNLIST, LB_GETCURSEL, NULL, NULL);
                Pokemon* selectedPokemon = 
                    (Pokemon*)SendDlgItemMessage(hDlgParent, IDLB_PKMNLIST, LB_GETITEMDATA, index, NULL);

                HWND hTxtName = GetDlgItem(hDlgParent, IDTXT_PKMNNAME);
                HWND hTxtType = GetDlgItem(hDlgParent, IDTXT_PKMNTYPE);
                HWND hTxtNumber = GetDlgItem(hDlgParent, IDTXT_PKMNNUMBER);

                setTextToComponent(hTxtName, selectedPokemon->name);
                setTextToComponent(hTxtType, selectedPokemon->type);
                setTextToComponent(hTxtNumber, to_string(selectedPokemon->number));

                //selectedPokemon->name.append("");

            }
            break;
            }
        }break;
        case IDBTN_ADDPKMN:
        {
            //MessageBox(hDlgParent, L"prueba", L"prueba", MB_OK);
            HWND hDialogPokeForm = CreateDialogW(
                GlobalhInstance,
                MAKEINTRESOURCE(IDD_POKEFORM),
                NULL,
                fDialogPokeForm
            );

            ShowWindow(hDialogPokeForm, SW_SHOW);
            DestroyWindow(hDlgParent);

        }
        break;

        }
    }
    break;
    }
    return FALSE;
}

INT_PTR CALLBACK fDialogPokeForm(HWND hDlgPokeForm, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE:
    {
        MessageBox(hDlgPokeForm, L"prueba", L"prueba", MB_OK);
    }
    break;
    case  WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDBTN_SAVE:
        {
            string pkmnName = getTextFromComponent(hDlgPokeForm, IDTXT_NAME);
            string pkmnType = getTextFromComponent(hDlgPokeForm, IDTXT_TYPE);
            string pkmnNumber = getTextFromComponent(hDlgPokeForm, IDTXT_NUMBER);

            Pokemon* newPokemon = new Pokemon;
            newPokemon->name = pkmnName;
            newPokemon->type = pkmnType;
            newPokemon->number = atoi(pkmnNumber.c_str());
            newPokemon->next = NULL;
            newPokemon->previous = NULL;

            if (PokeList == NULL)
            {
                PokeList = newPokemon;
            }
            else
            {
                Pokemon* lastPokemon = PokeList;
                while(lastPokemon->next != NULL)
                    lastPokemon = lastPokemon->next;

                lastPokemon->next = newPokemon;
                newPokemon->previous = lastPokemon;
            }

            HWND hDialogPokeApp = CreateDialogW(
                GlobalhInstance,
                MAKEINTRESOURCE(IDD_POKEAPP),
                NULL,
                fDialogPokeApp
            );

            ShowWindow(hDialogPokeApp, SW_SHOW);
            DestroyWindow(hDlgPokeForm);

        }
        break;
        case IDCANCEL:
        {
            HWND hDialogPokeApp = CreateDialogW(
                GlobalhInstance,
                MAKEINTRESOURCE(IDD_POKEAPP),
                NULL,
                fDialogPokeApp
            );

            ShowWindow(hDialogPokeApp, SW_SHOW);
            DestroyWindow(hDlgPokeForm);
        }
            break;
        }
    }
    break;
    }
    return FALSE;
}

string getTextFromComponent(HWND hParent, int idComponent)
{
    HWND hComponent = GetDlgItem(hParent, idComponent);
    wchar_t textFromComponent[50];
    GetWindowText(hComponent, textFromComponent, 50);

    wstring ws = wstring(textFromComponent);
    string str(ws.begin(), ws.end());
    return str;
}

void setTextToComponent(HWND hComponent, string text)
{
    wstring widestr = wstring(text.begin(), text.end());
    const wchar_t* componentText = widestr.c_str();
    SetWindowText(hComponent, componentText);
}
