#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <sstream>
#include <cmath>  
#include "resource2.h"
#define PI 3.14159265  
using namespace std;

BOOL CALLBACK DialogFun(HWND hwnd, UINT message,
	WPARAM wParam, LPARAM lParam)
{
	char Text[64];
	double x1, result1, x2, result2; 
	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hwnd, LOWORD(wParam));
			return TRUE;
		case IDC_BUTTON1: 
			SendDlgItemMessage(hwnd, IDC_EDIT11, WM_GETTEXT, 63, (LPARAM)Text);
			if (sscanf_s(Text, "%lf", &x1)<1)
			{
				MessageBox(hwnd, "Неверный формат вводимых данных",
					"Ошибка формата", MB_OK | MB_ICONHAND);
				return TRUE;
			}
			else if (x1 > 1 || x1 < -1) 
			{
				MessageBox(hwnd, "Нарушение области определения функции arcsin(x)!",
					"Ошибка ОДЗ", MB_OK | MB_ICONHAND);
				return TRUE;
			}
			if (LOWORD(wParam) == IDC_BUTTON1) { result1 = asin(x1) * 180.0 / PI; }
			sprintf(Text, "%f", result1);
			SendDlgItemMessage(hwnd, IDC_EDIT12, WM_SETTEXT, 0, (LPARAM)Text);
			sprintf_s(Text,"arcsin(%f) = %f", x1, result1);
			SendDlgItemMessage(hwnd, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)Text);
			return TRUE;
		case IDC_BUTTON2: 
			SendDlgItemMessage(hwnd, IDC_EDIT21, WM_GETTEXT, 63, (LPARAM)Text);
				if (sscanf_s(Text, "%lf", &x2)<1)
				{
					MessageBox(hwnd, "Неверный формат вводимых данных",
						"Ошибка формата", MB_OK | MB_ICONHAND); return TRUE;
				}
				else if (x2 > 1 || x2 < -1)
				{
					MessageBox(hwnd, "Нарушение области определения функции arccos(x)!",
						"Ошибка ОДЗ", MB_OK | MB_ICONHAND);
					return TRUE;
				}
			if (LOWORD(wParam) == IDC_BUTTON2) { result2 = acos(x2) * 180.0 / PI; }
			sprintf(Text, "%f", result2);
			SendDlgItemMessage(hwnd, IDC_EDIT22, WM_SETTEXT, 0, (LPARAM)Text);
				sprintf_s(Text, "arccos(%f) = %f", x2, result2);
			SendDlgItemMessage(hwnd, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)Text);
			return TRUE;
		case IDC_BUTTON3: 
			SendDlgItemMessage(hwnd, IDC_LIST1, LB_RESETCONTENT, 0, 0);
			return TRUE;
		}
	}
	return FALSE;
}

int APIENTRY WinMain( HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
					  LPSTR lpCmdLine,
					  int nCmdShow)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DialogFun);
	return 0;
}