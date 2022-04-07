#pragma once
#include <string>
#include <windows.h>
using namespace std;

string getTextFromComponent(HWND hDlgParent, int idComponent);
void setTextToComponent(HWND hComponent, string text);
wchar_t* stringToWchar(string str);

HINSTANCE GetHInstance();
void SetHInstance(HINSTANCE hInstance);

HWND CreateAndShowDialog(int idDialog, DLGPROC fDlg);
