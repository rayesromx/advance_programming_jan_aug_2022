#include "Utilerias.h"

HINSTANCE GlobalhInstance;

HINSTANCE GetHInstance()
{
    return GlobalhInstance;
}
void SetHInstance(HINSTANCE hInstance)
{
    GlobalhInstance = hInstance;
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

wchar_t* stringToWchar(string str)
{
    wstring ws = wstring(str.begin(), str.end());
    wchar_t* wcdynamic = new wchar_t[str.length()];
    int i = 0;
    for (; i < str.length(); i++)
    {
        wcdynamic[i] = ws[i];
    }
    wcdynamic[i] = 0;
    
    return wcdynamic;
}

void setTextToComponent(HWND hComponent, string text)
{
    wstring widestr = wstring(text.begin(), text.end());
    LPCWSTR componentText = widestr.c_str();
    SetWindowText(hComponent, componentText);
}

HWND CreateAndShowDialog(int idDialog, DLGPROC fDlg)
{
    HWND hDlg = CreateDialogW(
        GlobalhInstance,
        MAKEINTRESOURCE(idDialog),
        NULL,
        fDlg
    );
    ShowWindow(hDlg, SW_SHOW);
    return hDlg;
}