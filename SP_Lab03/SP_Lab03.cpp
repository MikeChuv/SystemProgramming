// SP_Lab03.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "SP_Lab03.h"

#define MAX_LOADSTRING 100

// ------ Глобальные переменные: ------
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

int mWindowWidth = 650;
int mWindowHeight = 500;

int windowCounter = 0;

// Имена окон
LPCWSTR lab02Name = L"Лабораторная №2";
LPCWSTR cppBuilderName = L"Lab03Builder";
LPCWSTR cSharpName = L"Form1";


// Дескрипторы для управляемых окон
HWND hLab02;
HWND hCppBuilder;
HWND hCSharp;

// Дескрипторы для кнопок сокрытия окон
HWND btnHideLab02;
const int idBtnHideLab02 = 0;
HWND btnHideCppBuilder;
const int idBtnHideCppBuilder = 1;
HWND btnHideCSharp;
const int idBtnHideCSharp = 2;

// Дескрипторы для кнопок переключения доступности окон
HWND btnDisableLab02;
const int idBtnDisableLab02 = 3;
HWND btnDisableCppBuilder;
const int idBtnDisableCppBuilder = 4;
HWND btnDisableCSharp;
const int idBtnDisableCSharp = 5;

// Кнопка закрытия окна 3 (приложение на C#)
HWND btnCloseCSharp;
const int idBtnCloseCSharp = 6;

// Кнопка для программного нажатия кнопки
// И выполнения команды пункта меню (вызов окна About)
HWND btnPushSquareItLab02;
const int idBtnPushSquareItLab02 = 7;
HWND btnSelectAboutMenuItemLab02;
const int idBtnSelectAboutMenuItemLab02 = 8;

// Кнопка переименования дочерних окон
HWND btnRenameChlidrenLab02;
const int idBtnRenameChlidrenLab02 = 9;

// Кнопка подсчета и переименования всех окон
HWND btnCountAndRename;
const int idBtnCountAndRename = 10;


// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK       RenameChildren(HWND, LPARAM);
BOOL CALLBACK       RenameChild(HWND, LPARAM);
BOOL CALLBACK       RenameWindow(HWND, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SPLAB03, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SPLAB03));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SPLAB03));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SPLAB03);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной
    
    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    MoveWindow(hWnd, 100, 100, mWindowWidth, mWindowHeight, true);

    if (!hWnd)
    {
        return FALSE;
    }

    int gridWidth = mWindowWidth / 4;
    int gridHeight = mWindowHeight / 12;
    int xoff = 20;
    int yoff = 20;

    int yRow = 20;
    btnHideLab02 = CreateWindow(L"BUTTON", L"Hide/Show Lab02", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, xoff, yRow, gridWidth, gridHeight, hWnd, (HMENU)idBtnHideLab02, hInstance, 0);
    btnHideCppBuilder = CreateWindow(L"BUTTON", L"Hide/Show Builder", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, gridWidth + xoff * 2, yRow, gridWidth, gridHeight, hWnd, (HMENU)idBtnHideCppBuilder, hInstance, 0);
    btnHideCSharp = CreateWindow(L"BUTTON", L"Hide/Show C#", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, gridWidth * 2 + xoff * 3, yRow, gridWidth, gridHeight, hWnd, (HMENU)idBtnHideCSharp, hInstance, 0);


    yRow = yRow + gridHeight + yoff;
    btnDisableLab02 = CreateWindow(L"BUTTON", L"Disable/Enable Lab02", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, xoff, yRow, gridWidth, gridHeight, hWnd, (HMENU)idBtnDisableLab02, hInstance, 0);
    btnDisableCppBuilder = CreateWindow(L"BUTTON", L"Disable/Enable Builder", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, gridWidth + xoff * 2, yRow, gridWidth, gridHeight, hWnd, (HMENU)idBtnDisableCppBuilder, hInstance, 0);
    btnDisableCSharp = CreateWindow(L"BUTTON", L"Disable/Enable C#", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, gridWidth * 2 + xoff * 3, yRow, gridWidth, gridHeight, hWnd, (HMENU)idBtnDisableCSharp, hInstance, 0);

   
    yRow = yRow + gridHeight + yoff;
    btnPushSquareItLab02 = CreateWindow(L"BUTTON", L"Push Square It", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,  xoff, yRow, gridWidth, gridHeight, hWnd, (HMENU)idBtnPushSquareItLab02, hInstance, 0);
    btnCloseCSharp = CreateWindow(L"BUTTON", L"Close C#", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,  gridWidth * 2 + xoff * 3, yRow, gridWidth, gridHeight, hWnd, (HMENU)idBtnCloseCSharp, hInstance, 0);

    yRow = yRow + gridHeight + yoff;
    btnSelectAboutMenuItemLab02 = CreateWindow(L"BUTTON", L"About Lab02", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,  xoff, yRow, gridWidth, gridHeight, hWnd, (HMENU)idBtnSelectAboutMenuItemLab02, hInstance, 0);

    yRow = yRow + gridHeight + yoff;
    btnRenameChlidrenLab02 = CreateWindow(L"BUTTON", L"Rename Chidren", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,  xoff, yRow, gridWidth, gridHeight, hWnd, (HMENU)idBtnRenameChlidrenLab02, hInstance, 0);

    yRow = yRow + gridHeight + yoff;
    btnCountAndRename = CreateWindow(L"BUTTON", L"Count and Rename", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,  xoff, yRow, gridWidth * 3 + 2 * xoff, gridHeight, hWnd, (HMENU)idBtnCountAndRename, hInstance, 0);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

   return TRUE;
}



BOOL CALLBACK RenameChildren(HWND hWnd, LPARAM lParam){
    SendMessage(hWnd, WM_SETTEXT, 0, lParam);
    return TRUE;
}

BOOL CALLBACK RenameChild(HWND hWnd, LPARAM lParam) {
    windowCounter++;
    TCHAR newName[MAX_LOADSTRING] = _T("Дочернее");
    TCHAR windowNumber[10];
    _itot_s(windowCounter, windowNumber, 10);
    _tcscat_s(newName, windowNumber);
    SendMessage(hWnd, WM_SETTEXT, NULL, LPARAM(newName));
    return TRUE;
}


BOOL CALLBACK RenameWindow(HWND hWnd, LPARAM lParam) {
    windowCounter++;
    TCHAR newName[MAX_LOADSTRING] = _T("Окно");
    TCHAR windowNumber[10];
    _itot_s(windowCounter, windowNumber, 10);
    _tcscat_s(newName, windowNumber);
    SendMessage(hWnd, WM_SETTEXT, NULL, LPARAM(newName));
    EnumChildWindows(hWnd, &RenameChild, lParam);
    return TRUE;
}


//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case idBtnHideLab02:
				{
					hLab02 = FindWindow(NULL, lab02Name);
					if (IsWindowVisible(hLab02))
						ShowWindow(hLab02, SW_HIDE);
					else
						ShowWindow(hLab02, SW_SHOWNOACTIVATE);
				}
				break;
            case idBtnHideCppBuilder:
				{
					hCppBuilder = FindWindow(NULL, cppBuilderName);
					if (IsWindowVisible(hCppBuilder))
						ShowWindow(hCppBuilder, SW_HIDE);
					else
						ShowWindow(hCppBuilder, SW_SHOWNOACTIVATE);
				}
				break;
            case idBtnHideCSharp:
				{
					hCSharp = FindWindow(NULL, cSharpName);
					if (IsWindowVisible(hCSharp))
						ShowWindow(hCSharp, SW_HIDE);
					else
						ShowWindow(hCSharp, SW_SHOWNOACTIVATE);
				}
				break;
            case idBtnDisableLab02:
				{
					hLab02 = FindWindow(NULL, lab02Name);
					if (IsWindowEnabled(hLab02))
						EnableWindow(hLab02, FALSE);
					else
						EnableWindow(hLab02, TRUE);
				}
				break;
            case idBtnDisableCppBuilder:
				{
					hCppBuilder = FindWindow(NULL, cppBuilderName);
					if (IsWindowEnabled(hCppBuilder))
						EnableWindow(hCppBuilder, FALSE);
					else
						EnableWindow(hCppBuilder, TRUE);
				}
				break;
            case idBtnDisableCSharp:
				{
					hCSharp = FindWindow(NULL, cSharpName);
					if (IsWindowEnabled(hCSharp))
						EnableWindow(hCSharp, FALSE);
					else
						EnableWindow(hCSharp, TRUE);
				}
				break;
            case idBtnCloseCSharp:
				{
					hCSharp = FindWindow(NULL, cSharpName);
					if (hCSharp && IsWindowEnabled(hCSharp))
						PostMessage(hCSharp, WM_QUIT, NULL, NULL);
				}
				break;
            case idBtnPushSquareItLab02:
				{
					hLab02 = FindWindow(NULL, lab02Name);
					HWND hBtnSquareIt = NULL;
					if (hLab02)
						hBtnSquareIt = FindWindowEx(hLab02, NULL, L"BUTTON", L"Square it!");
					if (hBtnSquareIt)
						SendMessage(hBtnSquareIt, BM_CLICK, 0, 0);
				}
				break;
            case idBtnSelectAboutMenuItemLab02:
				{
					hLab02 = FindWindow(NULL, lab02Name);
					if (hLab02)
						SendMessage(hLab02, WM_COMMAND, IDM_ABOUT, NULL);
				}
				break;
            case idBtnRenameChlidrenLab02:
            {
                hLab02 = FindWindow(NULL, lab02Name);
                if (hLab02)
                    EnumChildWindows(hLab02, &RenameChildren, LPARAM(L"Renamed!"));
            }
            break;

            case idBtnCountAndRename:
            {
                windowCounter = 0;
                EnumWindows(&RenameWindow, NULL);
            }
            break;





            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_RBUTTONDOWN:
		{
			hLab02 = FindWindow(NULL, lab02Name);
            if (hLab02)
			    SendMessage(hLab02, WM_RBUTTONDOWN, MK_RBUTTON, lParam);
		}
		break;
    case WM_RBUTTONUP:
		{
			hLab02 = FindWindow(NULL, lab02Name);
            if (hLab02)
			    SendMessage(hLab02, WM_RBUTTONUP, MK_RBUTTON, lParam);
		}
		break;

    case WM_LBUTTONDOWN:
		{
			hLab02 = FindWindow(NULL, lab02Name);
            if (hLab02) 
				SendMessage(hLab02, WM_LBUTTONDOWN, MK_LBUTTON, lParam);
		}
        break;
    case WM_LBUTTONUP:
		{
			hLab02 = FindWindow(NULL, lab02Name);
            if (hLab02)
				SendMessage(hLab02, WM_LBUTTONUP, MK_LBUTTON, lParam);
		}
        break;
    case WM_MOUSEMOVE:
		{
			hLab02 = FindWindow(NULL, lab02Name);
            if (hLab02) {
                POINT coords;
                coords.x = LOWORD(lParam);
                coords.y = HIWORD(lParam);
                ClientToScreen(hWnd, &coords);
                ScreenToClient(hLab02, &coords);
                SendMessage(hLab02, WM_MOUSEMOVE, wParam, MAKELONG(coords.x, coords.y));
            }
		}
		break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
