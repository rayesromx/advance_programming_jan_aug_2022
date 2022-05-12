#include<Windows.h>
#include <commctrl.h>
#include"resource.h"
#include <string>

using namespace std;

struct Envio {
	int cantidad;
	string domicilio;
	string producto;
	SYSTEMTIME fechaDeEnvio;
	string status;
};

struct Producto {
	wchar_t* rutaEnDiscoDeFoto1;
	wchar_t* rutaEnDiscoDeFoto2;
};

//nos sirve para crear dialogos
HINSTANCE global_hInstance;

string meses[]{"enero","febrero","marzo","abril"};

//INT_PTR CALLBACK fDlgMainDialog(HWND hParentDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)


INT_PTR CALLBACK fDlgTestDialog(HWND hParentDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	global_hInstance = hInstance;
	

	HWND hTestDialog = CreateDialogW(global_hInstance,
		MAKEINTRESOURCE(IDD_TEST),
		NULL,
		fDlgTestDialog);

	ShowWindow(hTestDialog, SW_SHOW);

	// Run the message loop.
	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

INT_PTR CALLBACK fDlgTestDialog(HWND hParentDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDBTN_LOADIMAGE:
		{
			Producto* nuevoProducto = new Producto;
			nuevoProducto->rutaEnDiscoDeFoto1 = new wchar_t[250];

			OPENFILENAME ofn;
			ZeroMemory(&ofn, sizeof(OPENFILENAME));

			ofn.hwndOwner = hParentDlg;
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.lpstrFile = nuevoProducto->rutaEnDiscoDeFoto1;
			ofn.nMaxFile = MAX_PATH;
			ofn.lpstrDefExt = L"bmp";
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
			ofn.lpstrFilter = L"textode ejemplo\0*.bmp";

			if (GetOpenFileName(&ofn)) {
				HBITMAP hBitmap1 = (HBITMAP)LoadImage(NULL, L"C:\\images\\pic.bmp", IMAGE_BITMAP, 512, 512, LR_LOADFROMFILE);
				HWND hPictureBox1 = GetDlgItem(hParentDlg, IDPB_IMAGE);
				SendMessage(hPictureBox1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap1);

				HBITMAP hBitmap2 = (HBITMAP)LoadImage(NULL, nuevoProducto->rutaEnDiscoDeFoto2, IMAGE_BITMAP, 512, 512, LR_LOADFROMFILE);
				HWND hPictureBox2 = GetDlgItem(hParentDlg, IDPB_IMAGE);
				SendMessage(hPictureBox2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap2);
			}
			else {
				MessageBox(hParentDlg, L"No ha seleccionado ninguna imagen", L"NO CARGAR", MB_ICONASTERISK);
			}
		}
		break;
		case IDOK:
		{
			SYSTEMTIME fecha;

			HWND hDateTimePicker = GetDlgItem(hParentDlg, IDDTP_DATE);
			DateTime_GetSystemtime(hDateTimePicker, &fecha);

			string fechaTexto = "La fecha seleccionada es: ";
			fechaTexto.append(to_string(fecha.wDay));
			fechaTexto.append(" de ");
			fechaTexto.append(meses[fecha.wMonth - 1]);
			fechaTexto.append(" del ");
			fechaTexto.append(to_string(fecha.wYear));
			
			wstring wFechaTexto = wstring(fechaTexto.begin(), fechaTexto.end());

			MessageBox(hParentDlg,
				wFechaTexto.c_str(),
				L"FECHA",
				MB_OK);

			
		}
		break;
		}
	}
	break;
	}
	return FALSE;
}