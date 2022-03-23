#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include "resource.h"
#include <string>
using namespace std;

HINSTANCE GlobalhInstance;

struct Pokemon
{
    string name;
    string type;
    int number;

    Pokemon* next;
    Pokemon* previous;
};

Pokemon* PokeList;


//LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fPokeApp(HWND hParent, UINT uMsg, WPARAM wParam, LPARAM lParam);
//INT_PTR CALLBACK fDigiApp(HWND hParent, UINT uMsg, WPARAM wParam, LPARAM lParam);

//linked lists functions
Pokemon* createNewPokemon(wchar_t*, wchar_t*, wchar_t*);
void insertNewPokemon(Pokemon*);
wchar_t* getTextFromComponent(HWND hParent, int idComponent);
void clearTextFromComponent(HWND hParent, int idComponent);
void setTextToComponent(HWND hParent, int idComponent, string text);

string convertWCHARtoString(wchar_t* wstr)
{
    wstring ws = wstring(wstr);
    string str(ws.begin(), ws.end());
    return str;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    GlobalhInstance = hInstance;
    PokeList = NULL;

    HWND hDialogPokeApp = CreateDialogW(
        GlobalhInstance,
        MAKEINTRESOURCE(IDD_POKEAPP),
        NULL, 
        fPokeApp
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

INT_PTR CALLBACK fPokeApp(HWND hParent, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
    {
        Pokemon* aux = PokeList;
        while (aux != NULL) {
            delete aux;
            aux = aux->next;
        }
    }
    break;
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDBTN_ADDPKMN:
        {
            wchar_t* pkmnName = getTextFromComponent(hParent, IDTXT_PKMNNAME);
            wchar_t* pkmnType = getTextFromComponent(hParent, IDTXT_PKMNTYPE);
            wchar_t* pkmnNumber = getTextFromComponent(hParent, IDTXT_PKMNNUMBER);

            Pokemon* newPokemon = createNewPokemon(pkmnName, pkmnType, pkmnNumber);
            insertNewPokemon(newPokemon);

            clearTextFromComponent(hParent, IDTXT_PKMNNAME);
            clearTextFromComponent(hParent, IDTXT_PKMNTYPE);
            clearTextFromComponent(hParent, IDTXT_PKMNNUMBER);

            //IDLB_POKELIST
            
            HWND hLBPokeList = GetDlgItem(hParent, IDLB_POKELIST);

            ///Esta linea agrega solamente agrega una cadena al listbox
            int listBoxIndex = SendMessage(hLBPokeList, LB_ADDSTRING, 0, (LPARAM)pkmnName);

            //ESTA LINEA AGREGA DATOS AL ELEMENTO QUE SE ACABA DE AGREBAR AL LISTBOX
            SendMessage(hLBPokeList, LB_SETITEMDATA, listBoxIndex, (LPARAM)(newPokemon));
        }
        break;

        case IDLB_POKELIST:
        {
            switch (HIWORD(wParam))
            {
            case LBN_SELCHANGE:
            {
                //OBTIENE EL INDICE DEL ELEMENTO DEL LISTBOX
                int index = SendDlgItemMessage(hParent, IDLB_POKELIST, LB_GETCURSEL, NULL, NULL);
                
                //OBTIENE LOS DATOS ASOCIADOS 
                Pokemon* selectedPokemon = (Pokemon*)
                    SendDlgItemMessage(hParent, IDLB_POKELIST, LB_GETITEMDATA, index, NULL);

                setTextToComponent(hParent, IDTXT_PKMNNAME , selectedPokemon->name);
                //setTextToComponent(hParent,, to_string(selectedPokemon->number));
                //setTextToComponent(hParent,, selectedPokemon->type);
                setTextToComponent(hParent, IDTXT_PKMNTYPE, selectedPokemon->type);

            }
            break;
            }
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
    return FALSE;
}

Pokemon* createNewPokemon(wchar_t* pkmnName, wchar_t* pkmnType, wchar_t* pkmnNumber)
{
    Pokemon* newPokemon;
    newPokemon = new Pokemon;

    newPokemon->name = convertWCHARtoString(pkmnName);
    newPokemon->type = convertWCHARtoString(pkmnType);
    newPokemon->number = atoi(convertWCHARtoString(pkmnNumber).c_str());

    newPokemon->next = NULL;
    newPokemon->previous = NULL;

    return newPokemon;
}

void insertNewPokemon(Pokemon* newPokemon)
{
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
}

wchar_t* getTextFromComponent(HWND hParent, int idComponent)
{
    HWND hComponent = GetDlgItem(hParent, idComponent);
    wchar_t* wText = new wchar_t[50];
    GetWindowText(hComponent, wText, 50);
    return wText;
}

void setTextToComponent(HWND hParent, int idComponent, string text)
{
     HWND hComponent = GetDlgItem(hParent, idComponent);
    wstring widestr = wstring(text.begin(), text.end());
    LPCWSTR componentText = widestr.c_str();
    SetWindowText(hComponent, componentText);
}

void clearTextFromComponent(HWND hParent, int idComponent)
{
    HWND hComponent = GetDlgItem(hParent, idComponent);
    SetWindowText(hComponent, L"");
}