#include "Utilities.h"


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

