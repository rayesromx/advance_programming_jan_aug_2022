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
    int number;
    string type;
    string firstAppearence;
    string image_path;

    Pokemon* previous;
    Pokemon* next;
};

Pokemon* PokeList;
Pokemon* selectedPokemon;

enum POKEFORM_ACTION {
        ADD_POKEFORM,
     UPDATE_POKEFORM,
     REMOVE_POKEFORM
};

POKEFORM_ACTION PKFAction;
LPWSTR fotoProducto1Nueva;


INT_PTR CALLBACK fDlgMainDialog(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fDlgPokeForm(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void DisplayMainDialog(HWND hwndPreviousDialog);
void DisplayPokeForm(HWND hwndPreviousDialog);

string getTextFromComponent(HWND hComponent)
{
    wchar_t text[50];
    GetWindowText(hComponent, text, 50);
    wstring ws = wstring(text);
    string str(ws.begin(), ws.end());
    return str;
}

void setTextToComponent(HWND hComponent, string text)
{
    wstring widestr = wstring(text.begin(), text.end());
    LPCWSTR componentText = widestr.c_str();
    SetWindowText(hComponent, componentText);
}

LPARAM* strToLparam(string str)
{
    wstring ws = wstring(str.begin(), str.end());
    const wchar_t* wc = ws.c_str();
    LPARAM lparamt = reinterpret_cast<LPARAM>(wc);
    LPARAM* lparam = new LPARAM;
    *lparam = lparamt;

    return lparam;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    GlobalhInstance = hInstance;
    PokeList = NULL;
    selectedPokemon = NULL;

    DisplayMainDialog(NULL);

    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

INT_PTR CALLBACK fDlgMainDialog(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HWND btnUpdate = GetDlgItem(hwnd, IDBTN_UPDATEPKMN);
    HWND btnRemove = GetDlgItem(hwnd, IDBTN_REMOVEPKMN);
    HWND btnAdd = GetDlgItem(hwnd, IDBTN_ADDPKMN);
    
    HWND lbPokeList = GetDlgItem(hwnd, IDLB_POKELIST);

    HWND lblName = GetDlgItem(hwnd, IDLBL_NAME);
    HWND lblNumber = GetDlgItem(hwnd, IDLBL_NUMBER);
    HWND lblType = GetDlgItem(hwnd, IDLBL_TYPE);
    HWND lblFirstAppearence = GetDlgItem(hwnd, IDLBL_APPEARENCE);

    HWND pcPhoto = GetDlgItem(hwnd, IDPC_PHOTO);

    switch (uMsg)
    {
    case WM_INITDIALOG:
    {
        SetWindowText(lblName, L"");
        SetWindowText(lblNumber, L"");
        SetWindowText(lblType, L"");
        SetWindowText(lblFirstAppearence, L"");

        ShowWindow(pcPhoto, SW_HIDE);

        EnableWindow(btnRemove, PokeList != NULL);
        EnableWindow(btnUpdate, PokeList != NULL);

        if (PokeList != NULL)
        {
            Pokemon* aux = PokeList;

            while (aux != NULL)
            {
                /*wstring ws = wstring(aux->name.begin(), aux->name.end());
                const wchar_t* wc = ws.c_str();
                LPARAM lparam = reinterpret_cast<LPARAM>(wc);*/

                int listBoxIndex = SendMessage(lbPokeList, LB_ADDSTRING, 0, *strToLparam(aux->name));
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
        case IDBTN_ADDPKMN:
        {
            PKFAction = ADD_POKEFORM;
            DisplayPokeForm(hwnd);
        }
        break;
        case IDBTN_UPDATEPKMN:
        {
            PKFAction = UPDATE_POKEFORM;
            DisplayPokeForm(hwnd);
        }
        break;
        case IDBTN_REMOVEPKMN:
        {
            PKFAction = REMOVE_POKEFORM;
            DisplayPokeForm(hwnd);
        }
        break;
        case IDLB_POKELIST:
        {
            switch(HIWORD(wParam))
            {
            case LBN_SELCHANGE:
            {
                int index = SendDlgItemMessage(hwnd, IDLB_POKELIST, LB_GETCURSEL, NULL, NULL);
                selectedPokemon = (Pokemon*)SendDlgItemMessage(hwnd, IDLB_POKELIST, LB_GETITEMDATA, index, NULL);

                setTextToComponent(lblName, selectedPokemon->name);
                setTextToComponent(lblNumber, to_string(selectedPokemon->number));
                setTextToComponent(lblType, selectedPokemon->type);
                setTextToComponent(lblFirstAppearence, selectedPokemon->firstAppearence);

            }
            break;
            }
        }
        break;

        }
    }
    break;
    }
    return FALSE;
}

INT_PTR CALLBACK fDlgPokeForm(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    HWND hTxtName = GetDlgItem(hwnd, IDTXT_NAME);
    HWND hTxtNumber = GetDlgItem(hwnd, IDTXT_NUMBER);
    HWND hTxtType = GetDlgItem(hwnd, IDTXT_TYPE);
    HWND hTxtAppreance = GetDlgItem(hwnd, IDTXT_APPEARENCE);
    HWND hBtnAccept = GetDlgItem(hwnd, IDBTN_ACCEPT);

    

    switch (uMsg)
    {
    case WM_INITDIALOG:
    {
        SetWindowText(hTxtName, L"");
        SetWindowText(hTxtNumber, L"");
        SetWindowText(hTxtType, L"");
        SetWindowText(hTxtAppreance, L"");

        EnableWindow(hTxtName, true);
        EnableWindow(hTxtNumber, true);
        EnableWindow(hTxtType, true);
        EnableWindow(hTxtAppreance, true);


        switch (PKFAction)
        {
        case ADD_POKEFORM:
            SetWindowText(hBtnAccept, L"Add");
            break;
        case UPDATE_POKEFORM:
            SetWindowText(hBtnAccept, L"Edit");
            EnableWindow(hTxtName, false);
            EnableWindow(hTxtNumber, false);
            break;
        case REMOVE_POKEFORM:
            SetWindowText(hBtnAccept, L"Delete");
            EnableWindow(hTxtName, false);
            EnableWindow(hTxtNumber, false);
            EnableWindow(hTxtType, false);
            EnableWindow(hTxtAppreance, false);
            break;
        }

    }
    break;

    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case IDBTN_LOADIMG:
        {
            OPENFILENAME ofn;
            ZeroMemory(&ofn, sizeof(OPENFILENAME));

            wchar_t* wc = new wchar_t[254];

            ofn.hwndOwner = hwnd;
            ofn.lStructSize = sizeof(OPENFILENAME);
            ofn.lpstrFile = wc;
            ofn.nMaxFile = MAX_PATH;
            ofn.lpstrDefExt = L"txt";
            ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
            ofn.lpstrFilter = L"Imagenes bmp\0*.bmp";

            if (GetOpenFileName(&ofn)) {
                HBITMAP hbFotoPP1 = (HBITMAP)LoadImage(GlobalhInstance, wc, IMAGE_BITMAP, 200, 200, LR_LOADFROMFILE);
                HWND hPbFotoPP1 = GetDlgItem(hwnd, PB_FOTOP1M);
                SendMessage(hPbFotoPP1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hbFotoPP1);
            }
            else {
                MessageBox(hwnd, L"No ha seleccionado ninguna imagen", L"NO CARGAR", MB_ICONASTERISK);
                break;
            }
        }
        break;
        case IDBTN_ACCEPT:
        {
            string name, number, type, appearence;
            switch (PKFAction)
            {
            case ADD_POKEFORM:
            {

                name = getTextFromComponent(hTxtName);
                number = getTextFromComponent(hTxtNumber);
                type = getTextFromComponent(hTxtType);
                appearence = getTextFromComponent(hTxtAppreance);

                Pokemon* newPokemon = new Pokemon;
                newPokemon->name = name;
                newPokemon->number = atoi(number.c_str());
                newPokemon->type = type;
                newPokemon->firstAppearence = appearence;
                newPokemon->previous = NULL;
                newPokemon->next = NULL;

                if (PokeList == NULL)
                {
                    PokeList = newPokemon;
                }
                else
                {
                    Pokemon* aux = PokeList;
                    while (aux->next != NULL)
                        aux = aux->next;

                    aux->next = newPokemon;
                    newPokemon->previous = aux;
                }

            }
                break;
            case UPDATE_POKEFORM:
               /*
               Get values from pokeform and update the node
               */
                break;
            case REMOVE_POKEFORM:
              
                break;
            }

            MessageBox(hwnd, L"Changes are already saved", L"Saved", MB_OK);
            DisplayMainDialog(hwnd);
        }
        break;
        case IDCANCEL:
        {
            int answer = MessageBox(hwnd, L"Changes won't be saved. Do you really want to cancel?", L"Canceling...", MB_OKCANCEL | MB_ICONASTERISK);
            if (answer == IDOK)
            {
                DisplayMainDialog(hwnd);
            }
        }
        break;

        }
    }
    break;

    }

    return FALSE;
}

void DisplayPokeForm(HWND hwndPreviousDialog)
{
    HWND hPokeForm =
        CreateDialogW(
            GlobalhInstance,
            MAKEINTRESOURCE(IDD_POKEFORM),
            NULL,
            fDlgPokeForm
        );
    ShowWindow(hPokeForm, SW_SHOW);
    if (hwndPreviousDialog != NULL)
    DestroyWindow(hwndPreviousDialog);
}

void DisplayMainDialog(HWND hwndPreviousDialog)
{
    HWND hMainDialog =
        CreateDialogW(
            GlobalhInstance,
            MAKEINTRESOURCE(IDD_MAINDIALOG),
            NULL,
            fDlgMainDialog
        );
    ShowWindow(hMainDialog, SW_SHOW);
    if(hwndPreviousDialog != NULL)
        DestroyWindow(hwndPreviousDialog);
}