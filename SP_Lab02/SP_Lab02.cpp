// SP_Lab02.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "SP_Lab02.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

HWND btnMaster; // управляющая кнопка
const int idBtnMaster = 0;

HWND btnSlave; // управляемая кнопка
const int idBtnSlave = 1;

HWND editText; // для введения числа для возведения в квадрат
const int idEditText = 2;

HWND staticText; // для вывода квадрата
const int idStaticText = 3;

HWND staticNCHITTEST;
const int idStaticNCHITTEST = 4;
int counterNCHITTEST = 0;

int mWindowWidth = 500;
int mWindowHeight = 400;

TCHAR mouseExpStr[800];

int mouseIsDown = 0; // для хранения текущего состояния кнопки мыши
POINT oldPoint;

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_SPLAB02, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SPLAB02));

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

    wcex.style          = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SPLAB02));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SPLAB02);
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
      CW_USEDEFAULT, mWindowWidth, CW_USEDEFAULT, mWindowWidth, nullptr, nullptr, hInstance, nullptr);

   MoveWindow(hWnd, 100, 100, mWindowWidth, mWindowHeight, true);

   if (!hWnd)
   {
      return FALSE;
   }


   btnMaster = CreateWindow(L"BUTTON", L"Push first!", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 275, 75, 100, 25, hWnd, (HMENU)idBtnMaster, hInstance, NULL);
   btnSlave = CreateWindow(L"BUTTON", L"Square it!", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 125, 75, 100, 25, hWnd, (HMENU)idBtnSlave, hInstance, NULL);
   editText = CreateWindow(L"EDIT", L"I am EDIT", WS_VISIBLE | WS_CHILD | NULL | WS_BORDER, 125, 15, 250, 25, hWnd, (HMENU)idEditText, hInstance, NULL);
   staticText = CreateWindow(L"STATIC", L"I am STATIC", WS_VISIBLE | WS_CHILD | NULL, 125, 125, 250, 125, hWnd, (HMENU)idStaticText, hInstance, NULL);
   staticNCHITTEST = CreateWindow(L"STATIC", L"I am STATIC", WS_VISIBLE | WS_CHILD | NULL, 125, 275, 250, 50, hWnd, (HMENU)idStaticNCHITTEST, hInstance, NULL);




   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

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
    case WM_RBUTTONDOWN:
    {
        POINT mouseP;
        mouseP.x = LOWORD(lParam);
        mouseP.y = HIWORD(lParam);
        TCHAR strX[10], strY[10];
        _itot_s(mouseP.x, strX, 10);
        _itot_s(mouseP.y, strY, 10);
        // _tcscat_s - так же макрос для TCHAR, аналог strcat
        // _T(x) - так же для TCHAR - используется для приведения к соотв. типу
        // не удалось понять, дают ли макросные функции сохранение \0 в конце строки
        _tcscat_s(strX, _T("\n"));
        _tcscat_s(strX, strY);
        SetWindowText(staticText, strX);
    }
    break;
    case WM_LBUTTONDOWN:
    {
        _tcscat_s(mouseExpStr, _T("Down! "));
        SetWindowText(staticText, mouseExpStr);
        mouseIsDown = 1;
    }
    break;
    case WM_LBUTTONUP:
    {
        _tcscat_s(mouseExpStr, _T("Up! "));
        SetWindowText(staticText, mouseExpStr);
        mouseIsDown = 0;
		ReleaseCapture();
    }
    break;
    case WM_LBUTTONDBLCLK:
    {
        _tcscat_s(mouseExpStr, _T("Double! "));
        SetWindowText(staticText, mouseExpStr);
    }
    break;
   
    case WM_MOUSEMOVE:
    {
		POINT coords;
		coords.x = LOWORD(lParam);
		coords.y = HIWORD(lParam);
        if (mouseIsDown)
        {
            SetCapture(hWnd);
            RECT mWindowRect;
            GetWindowRect(hWnd, &mWindowRect);
            //MoveWindow(hWnd,coords.x - oldPoint.x, coords.y - oldPoint.y, mWindowWidth, mWindowHeight, true);
            MoveWindow(hWnd, mWindowRect.left + coords.x - oldPoint.x, mWindowRect.top + coords.y - oldPoint.y, mWindowWidth, mWindowHeight, true);
        }
        else {
            oldPoint = coords;
        }
        
    }
    break;
    case WM_NCHITTEST:
    {
        counterNCHITTEST++;
        TCHAR strNCHITTEST[10];
        _itot_s(counterNCHITTEST, strNCHITTEST, 10);
        SetWindowText(staticNCHITTEST, strNCHITTEST);
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    break;


    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case idBtnMaster:
            {
                // первый вариант
                //SendMessage(btnSlave, BM_CLICK, 0, 0);
                // второй вариант
                SendMessage(btnSlave, WM_LBUTTONDOWN, 0, 0);
                SendMessage(btnSlave, WM_LBUTTONUP, 0, 0);
            }
			break;
            case idBtnSlave:
            {
                TCHAR editTextContent[MAX_LOADSTRING];
                GetWindowText(editText, editTextContent, MAX_LOADSTRING);
                // _ttoi универсальна для различных вариантов TCHAR
                // https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/atoi-atoi-l-wtoi-wtoi-l?redirectedfrom=MSDN&view=msvc-160
				int number = _ttoi(editTextContent);
                // _itot_s - макрос для вызова нужной функции, соотв. типу текущего варианта TCHAR
                // https://docs.microsoft.com/en-us/cpp/c-runtime-library/routine-mappings?view=msvc-160
                _itot_s(number * number, editTextContent, MAX_LOADSTRING, 10);
                SetWindowText(staticText, editTextContent);
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
