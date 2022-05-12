#include<Windows.h>
#include<CommCtrl.h>
#include"resource.h"
#include <string>

using namespace std;

HINSTANCE GLOBALhInstance;

string meses[]{ "enero", "febrero", "marzo" };

struct Envio
{
	int cantidad;
	string direccion;
	string producto;
	SYSTEMTIME fecha;
};
//
//struct Usuario {
//	int id;
//	str cont;
//	str usua;
//	int idVendedor;
//};
//
//struct Vend {
//	str empre;
//	str als;
//	wc foto;
//	int id;
//};
//
//struct Producto {
//	int id;
//	str nmb;
//	int cant;
//	int usuarioid;
//};
//
//struct Env {
//	str dir;
//	date fecha;
//	int productoId;
//	int usuarioid;
//};
//
//Vendedor 1 2 3 
//Usuario 







INT_PTR CALLBACK fDlgTest(HWND hParentDialog, UINT uMsg, WPARAM wparam, LPARAM lparam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
	{
		switch (LOWORD(wparam))
		{
		case IDBTN_CARGARIMAGEN:
		{
			wchar_t* rutaDeImageEnDisco = new wchar_t[250];
			OPENFILENAME ofn;
			ZeroMemory(&ofn, sizeof(OPENFILENAME));

			ofn.hwndOwner = hParentDialog;
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.lpstrFile = rutaDeImageEnDisco;
			ofn.nMaxFile = MAX_PATH;
			ofn.lpstrDefExt = L"bmp";
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY | OFN_NOCHANGEDIR;
			ofn.lpstrFilter = L"Imagenesitas\0*.bmp";

			if (GetOpenFileName(&ofn)) {
				HBITMAP hBitmap = (HBITMAP)
					LoadImage(
					NULL, 
					rutaDeImageEnDisco,
					IMAGE_BITMAP, 
					512, 512, 
					LR_LOADFROMFILE);
				HWND hPictureControl = GetDlgItem(hParentDialog, IDPC_IMAGEN);
				SendMessage(hPictureControl, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
			}
			else {
				//MessageBox(hParentDlg, L"No ha seleccionado ninguna imagen", L"NO CARGAR", MB_ICONASTERISK);
			}
		}
		break;

		case IDOK:
		{
			Envio* nuevoEnvio = new Envio;

			//SYSTEMTIME fecha;
			HWND hDTP = GetDlgItem(hParentDialog, IDDTP_FECHAENVIO);
			DateTime_GetSystemtime(hDTP, &nuevoEnvio->fecha);

			//La fecha seleccionada es: DD de MM del AAAA

			string texto = "La fecha seleccionada es: ";
			texto.append(to_string(nuevoEnvio->fecha.wDay));
			texto.append(" de ");
			texto.append(meses[nuevoEnvio->fecha.wMonth - 1]);
			texto.append(" del ");
			texto.append(to_string(nuevoEnvio->fecha.wYear));
			wstring wTexto = wstring(texto.begin(), texto.end());

			
			MessageBox(hParentDialog, wTexto.c_str(), L"titulo", MB_OK);
		}
		break;
		}
	}
	break;

	default:
		break;
	}


	return FALSE;
}

void leerProductosDeArchivo()
{
	fstream readStream;
	readStream.open("Producto.bin", ios::in | ios::binary | ios::ate);
	int totalSizeInByte = readStream.tellg();
	for (int i = 0; i < (totalSizeInByte / sizeof(PlayerInfo)); i++)
	{
		readStream.seekg(i * sizeof(PlayerInfo));
		readStream.read((char*)&players[i], sizeof(PlayerInfo));
		playerCounter++;
	}
	readStream.close();
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	leerProductosDeArchivo();


	GLOBALhInstance = hInstance;

	HWND hDlgTest = CreateDialogW(
		GLOBALhInstance,
		MAKEINTRESOURCE(IDD_TEST),
		NULL,
		fDlgTest
	);

	ShowWindow(hDlgTest, SW_SHOW);


	// Run the message loop.
	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	fstream archivo;
	archivo.open("playersData.bin", ios::out | ios::binary);
	for (int i = 0; i < playerCounter; i++)
	{
		archivo.write((char*)&players[i], sizeof(PlayerInfo));
	}
	archivo.close();

	return 0;
}