#include "WinApiUtils.h"
#include "resource.h"

HINSTANCE GlobalhInstance;

HINSTANCE GetHINSTANCE()
{
    return GlobalhInstance;
}

void SetHINSTANCE(HINSTANCE hi)
{
    GlobalhInstance = hi;
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
    if (hwndPreviousDialog != NULL)
        DestroyWindow(hwndPreviousDialog);
}