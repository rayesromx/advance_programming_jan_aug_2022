#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include"resource.h"

LRESULT CALLBACK fVentanaInicioSesion(
	HWND unnamedParam1,
	UINT unnamedParam2,
	WPARAM unnamedParam3,
	LPARAM unnamedParam4
);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	HWND hwndPrueba = CreateDialogW(
		hInstance,
		MAKEINTRESOURCE(IDD_INICIO_SESION),
		NULL,
		fVentanaInicioSesion);

	ShowWindow(hwndPrueba, SW_SHOWNORMAL);

	MSG msg = { };

	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}


LRESULT CALLBACK fVentanaInicioSesion(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG: {
		
	}break;

	case WM_COMMAND:
	{
		if (wParam == IDBTN_INICIAR_SESION)
		{
			//MessageBox(hwnd, NULL, NULL, MB_OK);
			//Crear otrodialog

			//HWND HWNDPRINCIPAL = CreateDialogW(
			//	hInstance,
			//	MAKEINTRESOURCE(IDD_VENTANA_PRINCIPAL),
			//	NULL,
			//	fVentanaPrincipal);

			//ShowWindow(HWNDPRINCIPAL, SW_SHOWNORMAL);
			PostQuitMessage(0);
		}
	}break;

	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK fVentanaPrincipal(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	//detectar si presiono boton para abrir otra pantalla
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}