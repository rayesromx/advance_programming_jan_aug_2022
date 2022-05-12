#pragma once
#include <windows.h>

void DisplayMainDialog(HWND hwndPreviousDialog);
void DisplayPokeForm(HWND hwndPreviousDialog);
HINSTANCE GetHINSTANCE();
void SetHINSTANCE(HINSTANCE hi);
