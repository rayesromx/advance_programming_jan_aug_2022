#include<Windows.h>
#include <commctrl.h>
#include "resource.h"
#include <string>

using namespace std;

HINSTANCE global_hInstance;

struct Envio {
	int cantidad;
	string calle;
	string estado;
	SYSTEMTIME fecha_envio;
};

INT_PTR CALLBACK fDlgMainDialog(HWND hParentDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	//este evento o mensaje se ejecuta solo una vez antes de que se muestre el dialogo
	case WM_INITDIALOG:
	{
		/*
		HMENU hMenuPpal = LoadMenu(global_hInstance, MAKEINTRESOURCE(IDMENU_PRINCIPAL));
		SetMenu(hParentDlg, hMenuPpal);
		*/

	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_EDIT_CUT: {
			HWND hMainDialog = CreateDialogW(
				global_hInstance,
				MAKEINTRESOURCE(IDD_MAINDIALOG),
				NULL,
				fDlgMainDialog
			);

			ShowWindow(hMainDialog, SW_SHOW);
		}
			break;
		case ID_EDIT_COPY:
		{}
			break;
		case ID_HELP_EXIT:
		{
			PostQuitMessage(0);
		}
		break;
		case IDOK:
		{
			HWND hDatePick = GetDlgItem(hParentDlg, IDDTP_DATE);
			Envio *nuevoEnvio = new Envio;

			//obtener la fecha del datetime picker y guardarla en una
			// variable de la estructura Envio
			DateTime_GetSystemtime(hDatePick, &nuevoEnvio->fecha_envio);
			string textoFecha = "La fecha que seleccionaste es ";
			textoFecha.append(to_string(nuevoEnvio->fecha_envio.wDay));
			textoFecha.append("/");
			textoFecha.append(to_string(nuevoEnvio->fecha_envio.wMonth));
			textoFecha.append("/");
			textoFecha.append(to_string(nuevoEnvio->fecha_envio.wYear));
			//La fecha que seleccionaste es 19/9/1991

			wstring wTextoFecha = wstring(textoFecha.begin(), textoFecha.end());

			MessageBox(hParentDlg, wTextoFecha.c_str(), L"Fecha", MB_OK);
		}
		break;
		}
	}
	break;
	}
	return FALSE;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	global_hInstance = hInstance;
	
	HWND hMainDialog = CreateDialogW(
		global_hInstance,
		MAKEINTRESOURCE(IDD_MAINDIALOG),
		NULL,
		fDlgMainDialog
	);

	ShowWindow(hMainDialog, SW_SHOW);

	// Run the message loop.

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}