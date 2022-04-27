#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <commctrl.h>
#include <ctime>
#include "resource.h"
#include "RERUtils.h"
using namespace std;

HINSTANCE global_hInstance;

INT_PTR CALLBACK fDlgSimpleLinkedListExamples(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fDlgDoublyLinkedListExamples(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK fDlgMainWindow(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


struct Envio
{
	SYSTEMTIME  fechaEnvio;
	string colonia;
		int cantidad;

};


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	global_hInstance = hInstance;
	HWND hMW = RERCreateDialog(hInstance, IDD_MAINWINDOW, fDlgMainWindow);

	if (hMW == NULL)
		return 0;

	RERShowDialog(hMW);

	// Run the message loop.

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}


INT_PTR CALLBACK fDlgSimpleLinkedListExamples(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HMENU hMenu = LoadMenu(global_hInstance, MAKEINTRESOURCE(IDMENU_LISTACTIONS));
		SetMenu(hwnd, hMenu);

		HWND hDatePick = GetDlgItem(hwnd, IDDTP_DATE);
		//DateTime_SetFormat(hDatePick, L"09/19/1991");
		SYSTEMTIME  dts;
		//DateTime_GetSystemtime(hDatePick, &dts);

		//DateTime_SetSystemtime()
		
	}
	break;

	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDBTN_SLL_ADDNEWITEM:
		{
			HWND hDatePick =  GetDlgItem(hwnd, IDDTP_DATE);
			SYSTEMTIME  fechaEnvio;
			DateTime_GetSystemtime(hDatePick, &fechaEnvio);
			//int anio = fechaEnvio.wYear;

			
			string fechaStr = "";
			fechaStr.append(to_string(fechaEnvio.wYear));
			fechaStr.append("-");
			fechaStr.append(to_string(fechaEnvio.wMonth));
			fechaStr.append("-");
			fechaStr.append(to_string(fechaEnvio.wDay));
			


			string datePickerTime = RERGetText(hDatePick);

			time_t tiempoActual;
			tm infoTiempo;
			time(&tiempoActual);
			localtime_s(&infoTiempo, &tiempoActual);

			tm* ltm = new tm;
			char* pch;
			char* dup = _strdup(datePickerTime.c_str());
			rsize_t strmax = sizeof dup;
			char* next_token;
			pch = strtok_s(dup,"/",&next_token);
			ltm->tm_mon = atoi(strtok_s(NULL, "/", &next_token));
			ltm->tm_year = atoi(strtok_s(NULL, "/", &next_token));
			ltm->tm_mday = atoi(pch);

			


			char day[5];
			char month[5];
			char year[5];


			++infoTiempo.tm_mon;
			infoTiempo.tm_year += 1900;


			_itoa_s(infoTiempo.tm_mday, day, 10);
			_itoa_s(infoTiempo.tm_mon, month, 10);
			_itoa_s(infoTiempo.tm_year, year, 10);
		}
		break;
		case IDCANCEL:
			RERCreateAndShowDialog(global_hInstance, IDD_MAINWINDOW, fDlgMainWindow, hwnd);
			break;
		case ID_INSERT_INSERTATBEGINING:
		{

		}
		break;
		case ID_INSERT_INSERTATTHEEND:
		{

		}
		break;
		case ID_INSERT_INSERTATCUSTOMPOSITION:
		{

		}
		break;
		case ID_DELETE_DELETEFIRST:
		{

		}
		break;
		case ID_DELETE_DELETELASTNODE:
		{

		}
		break;
		case ID_DELETE_DELETEACUSTOMP:
		{

		}
		break;
		case ID_HOME:
		{

		}
		break;
		case ID_UPDATE:
		{

		}
		break;

		}
		
	}
	return FALSE;
}

INT_PTR CALLBACK fDlgDoublyLinkedListExamples(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HMENU hMenu = LoadMenu(global_hInstance, MAKEINTRESOURCE(IDMENU_LISTACTIONS));
		SetMenu(hwnd, hMenu);
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			RERCreateAndShowDialog(global_hInstance, IDD_MAINWINDOW, fDlgMainWindow, hwnd);
			break;
		}
		break;

	}
	return FALSE;
}


INT_PTR CALLBACK fDlgMainWindow(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HMENU hMenu = LoadMenu(global_hInstance, MAKEINTRESOURCE(IDR_MENU1));
		SetMenu(hwnd, hMenu);
	}
	break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		/*case ID_ABOUT_EXIT:
		{
			MessageBox(hwnd, L"Prueba", L"pruebita", MB_OK);
		}*/
		break;
		case IDBTN_MW_EXIT:
		{
			if (REROKCancelMBox(L"Are you sure to close this app?", L"Closing app...") == IDOK)
			{
				PostQuitMessage(0);
				return 0;
			}
		}
		break;
		case IDBTN_MW_OPENDOUBLYLINKEDLISTS:
		{
			RERCreateAndShowDialog(global_hInstance, IDD_DOUBLYLISTS, fDlgDoublyLinkedListExamples, hwnd);
		}
			break;
		case IDBTN_MW_OPENSIMPLELINKEDLISTS:
		{
			RERCreateAndShowDialog(global_hInstance, IDD_SIMPLELISTS, fDlgSimpleLinkedListExamples, hwnd);
		}
			break;
		}
	}
	break;
	}
	return FALSE;
}

//https://conclase.net/winapi/curso/macros