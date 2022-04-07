#pragma once
#include <windows.h>
#include <string>


HWND RERCreateDialog(HINSTANCE hInstance, int nIdDialogResource, DLGPROC fCallback);

void RERShowDialog(HWND hNewDialog, HWND hOldDialog = NULL);

int REROKCancelMBox(LPCWSTR title, LPCWSTR caption);

HWND RERCreateAndShowDialog(HINSTANCE hInstance, int nIdDialogResource, DLGPROC fCallback, HWND hOldDialog = NULL);

std::string RERGetText(HWND hwnd);