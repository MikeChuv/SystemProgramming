// SP_Lab05.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "SP_Lab05.h"
#include <stdlib.h>

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// для задания 1
HWND btnTask1;
const int idBtnTask1 = 1;
bool flagTask1 = false;
COLORREF desktopMeanColor; //значение цвета рабочего стола

// для задания 2
HWND btnTask2;
const int idBtnTask2 = 2;
bool flagTask2 = false;

// для задания 3
HWND btnTask3;
const int idBtnTask3 = 3;
bool flagTask3 = false;
RECT circleRect = { 0, 0, 50, 50 }; // начальный bbox для круга
int dx = 20, dy = 20; // скорость движения круга
HWND hwndDesktop;
HWND hwndCSharp;
HDC hdcDesktop;
HDC hdcClient;
HDC hdcCSharp;
const static int idTimer = 5; // идентификатор таймера
static int timerTick = 0; // счетчик тиков

// для задания 4
HWND btnTask4;
const int idBtnTask4 = 4;
bool flagTask4 = false;
bool isDrawingState = false; // флаг состояния, когда зажата ЛКМ
POINT PBegin, PEnd; // начало и конец линии
HPEN pen;
int penWidth = 5;
RECT editorRect = { 200, 30, 800, 450 }; // прямоугольник редактора



// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
COLORREF            GetDesktopMeanColor(); // получение цвета рабочего стола
void                Task1OnPaint(HWND, HDC); // вынесение выполнения задания 1 в функцию
void                DrawFlag(HDC, int x0, int y0, int width, int height); // рисование флага
void                Task2OnPaint(HWND); // вынесение выполнения задания 1 в функцию
void                DrawCircle(HDC); // рисование круга в контекст
void                Circles(HWND); // рисования кругов (задание 3)
bool                isInEditor(DWORD); // мышь внутри области редактора

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
    LoadStringW(hInstance, IDC_SPLAB05, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SPLAB05));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SPLAB05));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SPLAB05);
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

   if (!hWnd)
   {
      return FALSE;
   }


   btnTask1 = CreateWindow(L"BUTTON", L"Desktop color", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 20, 40, 100, 60, hWnd, (HMENU)idBtnTask1, hInstance, 0);
   btnTask2 = CreateWindow(L"BUTTON", L"RU Flag", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 20, 110, 100, 60, hWnd, (HMENU)idBtnTask2, hInstance, 0);
   btnTask3 = CreateWindow(L"BUTTON", L"Circle", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 20, 180, 100, 60, hWnd, (HMENU)idBtnTask3, hInstance, 0);
   btnTask4 = CreateWindow(L"BUTTON", L"Editor", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 20, 250, 100, 60, hWnd, (HMENU)idBtnTask4, hInstance, 0);

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
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case idBtnTask1: {
                flagTask2 = flagTask3 = flagTask4 = false;
                flagTask1 = !flagTask1;
                desktopMeanColor = GetDesktopMeanColor();
                InvalidateRect(hWnd, NULL, true);
                UpdateWindow(hWnd);
            } 
            break;
            case idBtnTask2: {
                flagTask1 = flagTask3 = flagTask4 = false;
                flagTask2 = !flagTask2; 
                InvalidateRect(hWnd, NULL, true);
                UpdateWindow(hWnd);
                Task2OnPaint(hWnd);
            }
            break;
            case idBtnTask3: {
                flagTask1 = flagTask2 = flagTask4 = false;
                flagTask3 = !flagTask3;
                if (flagTask3) {
                    // получаем контекст устройства для каждого окна
                    hdcClient = GetDC(hWnd);
                    hwndDesktop = GetDesktopWindow();
                    hdcDesktop = GetDC(hwndDesktop);
                    hwndCSharp = FindWindow(NULL, L"Form1");
                    if (hwndCSharp) hdcCSharp = GetDC(hwndCSharp);
                    timerTick = 0; // обнулить таймер
                    SetTimer(hWnd, idTimer, 50, (TIMERPROC)NULL); // таймер с периодом 50мс
                }
                else {
                    // очистка областей
                    InvalidateRect(hwndDesktop, &circleRect, true);
                    InvalidateRect(hWnd, &circleRect, true);
                    if (hwndCSharp) InvalidateRect(hwndCSharp, &circleRect, true);
                    // освобождение контекста
                    ReleaseDC(hwndDesktop, hdcDesktop);
                    ReleaseDC(hWnd, hdcClient);
                    if (hdcCSharp) ReleaseDC(hwndCSharp, hdcCSharp);
                    KillTimer(hWnd, idTimer); // остановить таймер
                }
            }
            break;
            case idBtnTask4: {
                flagTask1 = flagTask2 = flagTask3 = false;
                flagTask4 = !flagTask4;
                InvalidateRect(hWnd, NULL, true);
                UpdateWindow(hWnd);
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
    case WM_SIZING:
    {
        UpdateWindow(hWnd);
    }
    break;
    case WM_TIMER:
    {
        if (flagTask3) {
            ++timerTick;
            Circles(hWnd);
        }
        else {
            KillTimer(hWnd, idTimer); // остановить таймер
        }
    }
    break;
    case WM_LBUTTONDOWN:
    {
        if (flagTask4 && isInEditor(lParam))
        {
            isDrawingState = true;
            PEnd = PBegin = { LOWORD(lParam) , HIWORD(lParam) };
            pen = CreatePen(PS_SOLID, penWidth, RGB(rand() % 256, rand() % 256, rand() % 256));
        }
    }
    break;
    case WM_LBUTTONUP:
    {
        // если в состоянии рисования линии отпускаем ЛКМ
        if (isDrawingState && isInEditor(lParam))
        {
            HDC hdc = GetDC(hWnd);
            SelectObject(hdc, pen);
            // чтобы оставались только линии R2_NOTMASKPEN, R2_XORPEN, R2_NOTXORPEN 
            SetROP2(hdc, R2_COPYPEN);
            MoveToEx(hdc, PBegin.x, PBegin.y, nullptr);
            LineTo(hdc, LOWORD(lParam), HIWORD(lParam));
            ReleaseDC(hWnd, hdc);
            DeleteObject(pen);
            isDrawingState = false;
        }
    }
    break;
    case WM_MOUSEMOVE:
    {
        // если в состоянии рисования линии двигаем мышь
        if (isDrawingState && isInEditor(lParam))
        {
            HDC hdc = GetDC(hWnd);
            SelectObject(hdc, pen);
            // чтобы оставались только линии R2_NOTMASKPEN, R2_XORPEN, R2_NOTXORPEN 
            SetROP2(hdc, R2_XORPEN);
            MoveToEx(hdc, PBegin.x, PBegin.y, nullptr);
            LineTo(hdc, PEnd.x, PEnd.y);
            MoveToEx(hdc, PBegin.x, PBegin.y, nullptr);
            LineTo(hdc, LOWORD(lParam), HIWORD(lParam));
            PEnd = { LOWORD(lParam) , HIWORD(lParam) };
            ReleaseDC(hWnd, hdc);
        }  
    }
    break;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			if (flagTask1) {
                Task1OnPaint(hWnd, hdc);
			}
            if (flagTask4) {
                HPEN pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
                SelectObject(hdc, pen);
                Rectangle(hdc, editorRect.left, editorRect.top, editorRect.right, editorRect.bottom);
                DeleteObject(pen);
            }
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

COLORREF GetDesktopMeanColor() {
    HWND hwndDesktop = GetDesktopWindow();
    HDC hdcDesktop = GetDC(hwndDesktop);
    RECT rec;
    int red = 0, green = 0, blue = 0, count = 0;
    GetWindowRect(hwndDesktop, &rec);
    // Используем метод Монте-Карло для уменьшения количества вычислений
    for (int i = 0; i < 30; ++i){
        int x = (double)rand() / (RAND_MAX + 1) * rec.right;
        int y = (double)rand() / (RAND_MAX + 1) * rec.bottom;
		count++;
		COLORREF color = GetPixel(hdcDesktop, x, y);
		red += GetRValue(color);
		green += GetGValue(color);
		blue += GetBValue(color);
	}
    red = int(red / count);
    green = int(green / count);
    blue = int(blue / count);
    ReleaseDC(hwndDesktop, hdcDesktop);
    return RGB(red, green, blue);
}

void Task1OnPaint(HWND hWnd, HDC hdc) {
    RECT hWnd_rect;
    GetWindowRect(hWnd, &hWnd_rect);
    hWnd_rect.top = 0;
    hWnd_rect.left = 0;
    FillRect(hdc, &hWnd_rect, (HBRUSH)CreateSolidBrush(desktopMeanColor));
    SetBkColor(hdc, desktopMeanColor);

    // Пишем курсивным жирным шрифтом с поворотом в 40 градусов
    HGDIOBJ font = CreateFont(64, 0, 40, 0, FW_BOLD, true, false, false, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, FF_DONTCARE, L"Courier new");
    SetTextColor(hdc, RGB(2, 70, 150));
    SelectObject(hdc, font);
    TextOut(hdc, 200, 60, L"Привет мир))0)", 15);

    // Рисуем скругленный прямоугольник случайным цветом
    SelectObject(hdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
    int xr = 200, yr = 250;
    RoundRect(hdc, xr, yr, xr + 100, yr + 100, 50, 50);

    // Рисуем круг серой кистью
    SelectObject(hdc, GetStockObject(LTGRAY_BRUSH));
    Ellipse(hdc, xr + 100, yr + 100, xr + 350, yr + 250);

    // Рисуем облако из четырех полукругов с диагональной штриховкой
    SelectObject(hdc, CreateHatchBrush(HS_FDIAGONAL, RGB(255, 255, 255)));
    int _size = 70, d1 = 3 * _size, d2 = 2 * _size;
    int x = 500, y = 250;
    Chord(hdc, x, y, x + d1, y + d2, x + d1, y + d2 / 2, x, y + d2 / 2);
    int dx = _size;
    Chord(hdc, x, y + d2 / 4, x + dx, y + 3 * d2 / 4, x, y + d2 / 2, x + d1, y + d2 / 2);
    Chord(hdc, x + dx, y + d2 / 4, x + 2 * dx, y + 3 * d2 / 4, x, y + d2 / 2, x + d1, y + d2 / 2);
    Chord(hdc, x + 2 * dx, y + d2 / 4, x + 3 * dx, y + 3 * d2 / 4, x, y + d2 / 2, x + d1, y + d2 / 2);

    ReleaseDC(hWnd, hdc);

    flagTask1 = false;
}

void DrawFlag(HDC hdc, int x0, int y0, int width, int height) {

    HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
    HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
    HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));

    RECT flagRect = { x0, y0, x0 + width, y0 + height };
    FillRect(hdc, &flagRect, whiteBrush);
    flagRect = { x0, y0 + height, x0 + width, y0 + 2 * height };
    FillRect(hdc, &flagRect, blueBrush);
    flagRect = { x0, y0 + 2 * height, x0 + width, y0 + 3 * height };
    FillRect(hdc, &flagRect, redBrush);
    // очищаем ресурсы
    DeleteObject(whiteBrush);
    DeleteObject(blueBrush);
    DeleteObject(redBrush);
}


void Task2OnPaint(HWND hWnd) {
    HDC hdc;
    
    // рисование на рабочем столе
    HWND hwndDesktop = GetDesktopWindow();
    hdc = GetWindowDC(hwndDesktop);
    DrawFlag(hdc, 0, 0, 300, 50);
    ReleaseDC(hwndDesktop, hdc);

    // рисование в рабочей области окна
    hdc = GetDC(hWnd);
    DrawFlag(hdc, 350, 0, 300, 50);
    ReleaseDC(hWnd, hdc);

    // рисование на всей области окна
    hdc = GetWindowDC(hWnd);
    DrawFlag(hdc, 0, 0, 300, 50);
    ReleaseDC(hWnd, hdc);

    flagTask2 = false;
}

void DrawCircle(HDC hdc){
    HBRUSH brush = CreateSolidBrush(RGB(0, 100, 200));
    SelectObject(hdc, brush);
    Ellipse(hdc, circleRect.left, circleRect.top, circleRect.right, circleRect.bottom);
    DeleteObject(brush);
}


void Circles(HWND hWnd) {
    InvalidateRect(hwndDesktop, &circleRect, true);
    UpdateWindow(hwndDesktop);

    InvalidateRect(hWnd, &circleRect, true);
    UpdateWindow(hWnd);

    if (hdcCSharp) {
        InvalidateRect(hwndCSharp, &circleRect, true);
        UpdateWindow(hwndCSharp);
    }

    int shift = 1;
    circleRect = { timerTick * shift, timerTick * shift, timerTick * shift + 100, timerTick * shift + 100 };

    DrawCircle(hdcDesktop);
    DrawCircle(hdcClient);
    if (hdcCSharp) DrawCircle(hdcCSharp);
}

bool isInEditor(DWORD lParam) {
    return  LOWORD(lParam) > editorRect.left + penWidth &&
            LOWORD(lParam) < editorRect.right - penWidth &&
            HIWORD(lParam) > editorRect.top + penWidth &&
            HIWORD(lParam) < editorRect.bottom - penWidth;
}