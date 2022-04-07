#include "RERUtils.h"

HWND RERCreateDialog(HINSTANCE hInstance, int nIdDialogResource, DLGPROC fCallback)
{
    HWND hDialog = CreateDialogW(hInstance, MAKEINTRESOURCE(nIdDialogResource), NULL, fCallback);

    if (hDialog == NULL)
    {
        MessageBox(hDialog, L"FATAL ERROR", L"An error has ocurred when creating a dialog.", MB_OK | MB_ICONERROR);
        return NULL;
    }
    return hDialog;
}

void RERShowDialog(HWND hNewDialog, HWND hOldDialog)
{
    ShowWindow(hNewDialog, SW_SHOW);
    if (hOldDialog != NULL)
    {
        DestroyWindow(hOldDialog);
    }
}

int REROKCancelMBox(LPCWSTR message, LPCWSTR title)
{
    return MessageBox(NULL, message, title, MB_OKCANCEL | MB_ICONASTERISK);
}

HWND RERCreateAndShowDialog(HINSTANCE hInstance, int nIdDialogResource, DLGPROC fCallback, HWND hOldDialog)
{
    HWND hMW = RERCreateDialog(hInstance, nIdDialogResource, fCallback);

    if (hMW == NULL)
        return NULL;

    RERShowDialog(hMW, hOldDialog);
}

std::string RERGetText(HWND hwnd) {
    int length = GetWindowTextLength(hwnd);
    if (length < 1)
        return "";
     wchar_t cText[50];
    GetWindowText(hwnd, cText, ++length);
    std::wstring ws = std::wstring(cText);
    std::string sText(ws.begin(), ws.end());
    return sText;
}