
#include <windows.h>
#include <string>
#include "resource.h"

using namespace std;

HINSTANCE GlobalHIns;

INT_PTR CALLBACK fDlg1(HWND hParentDialog, UINT uMsg, WPARAM wparam, LPARAM lparam);
INT_PTR CALLBACK fDlg2(HWND hParentDialog, UINT uMsg, WPARAM wparam, LPARAM lparam);
INT_PTR CALLBACK fDlg3(HWND hParentDialog, UINT uMsg, WPARAM wparam, LPARAM lparam);

void CreateAndShowDialog(HWND hCurrentDialog, int idDialog, DLGPROC proc)
{
    HWND hNewDialog = 
        CreateDialogW(
        GlobalHIns,
        MAKEINTRESOURCE(idDialog),
        NULL,
        proc
    );

    ShowWindow(hNewDialog, SW_SHOW);
    if(hCurrentDialog != NULL)
        DestroyWindow(hCurrentDialog);
}

void HandleCommonMenuOptions(HWND hParentDialog, WPARAM wparam)
{
    switch (LOWORD(wparam))
    {
    case IDBTN_SHOW_DLG1:
    {
        CreateAndShowDialog(hParentDialog, IDD_DIALOG1, fDlg1);
    }
    break;
    case IDBTN_SHOW_DLG2:
    {
        CreateAndShowDialog(hParentDialog, IDD_DIALOG2, fDlg2);
    }
    break;
    case IDBTN_SHOW_DLG3:
    {
        CreateAndShowDialog(hParentDialog, IDD_DIALOG3, fDlg3);
    }
    break;
    }
}

void LoadDialogMenuAndDisableOption(HWND hParentDialog, int idMenuItem)
{
    HMENU hMenu = LoadMenu(GlobalHIns, MAKEINTRESOURCE(IDR_MENU1));
    SetMenu(hParentDialog, hMenu);
    EnableMenuItem(hMenu, idMenuItem, MF_GRAYED);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    GlobalHIns = hInstance;

    CreateAndShowDialog(NULL, IDD_DIALOG1, fDlg1);
    // Run the message loop.

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

INT_PTR CALLBACK fDlg1(HWND hParentDialog, UINT uMsg, WPARAM wparam, LPARAM lparam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
    {
        LoadDialogMenuAndDisableOption(hParentDialog, IDBTN_SHOW_DLG1);
    }
    case WM_COMMAND: 
    {
        HandleCommonMenuOptions(hParentDialog, wparam);
        switch (LOWORD(wparam))
        {
        case IDBTN1:
        {
            MessageBox(hParentDialog, L"Buenos dias", L"Saludo", MB_OK);
        }
        break;
        }

    }
    break;
    }
    return FALSE;
}

INT_PTR CALLBACK fDlg2(HWND hParentDialog, UINT uMsg, WPARAM wparam, LPARAM lparam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
    {
        LoadDialogMenuAndDisableOption(hParentDialog, IDBTN_SHOW_DLG2);
    }
    break;
    case WM_COMMAND:
    {
        HandleCommonMenuOptions(hParentDialog, wparam);
        switch (LOWORD(wparam))
        {
        case IDBTN2:
        {
            MessageBox(hParentDialog, L"Buenas tardes", L"Saludo", MB_OK);
        }
        break;
        }
    }
    break;
    }
   return FALSE;
}

INT_PTR CALLBACK fDlg3(HWND hParentDialog, UINT uMsg, WPARAM wparam, LPARAM lparam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
    {
        LoadDialogMenuAndDisableOption(hParentDialog, IDBTN_SHOW_DLG3);
    }
    break;
    case WM_COMMAND:
    {
       HandleCommonMenuOptions(hParentDialog, wparam);
       switch (LOWORD(wparam))
       {
       case IDBTN3:
       {
           MessageBox(hParentDialog, L"Buenas noches", L"Saludo", MB_OK);
       }
       break;
       }
    }
    break;
    }
return FALSE;
}