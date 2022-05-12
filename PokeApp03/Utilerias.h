#pragma once
#include <string>
#include <windows.h>
using namespace std;

wchar_t* stringToWchar(string str);

string getTextFromComponent(HWND hDlgParent, int idComponent); 
void setTextToComponent(HWND hComponent, string text);

HINSTANCE GetHInstance();
void SetHInstance(HINSTANCE hInstance);

HWND CreateAndShowDialog(int idDialog, DLGPROC fDlg);
