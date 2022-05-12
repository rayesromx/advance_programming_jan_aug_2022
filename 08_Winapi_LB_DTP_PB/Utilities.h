#pragma once
#include <windows.h>
#include <string>

using namespace std;
LPARAM* strToLparam(string str);
void setTextToComponent(HWND hComponent, string text);
string getTextFromComponent(HWND hComponent);
