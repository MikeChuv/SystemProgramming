// winapi_bitmap.cpp : Определяет точку входа для приложения.
//

#pragma comment(lib, "Msimg32.lib")

#include "framework.h"
#include "resource.h"
#include "winapi_bitmap.h"


#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// задание 1 - битовые карты
HBITMAP hBliss;
HBITMAP hMower;
HWND btnPlayAnimation;
const int idBtnPlayAnimation = 0;
bool isPlayingAnimation = false;
const int idTimer = 1;
static int timerTick = 0;

HDC clientHDC;
HDC blissHDC;
HDC mowerHDC;

// задание 3 - метафайлы
HWND btnMetafile;
const int idBtnMetafile = 1;
bool isPlayingMetafile = 0;



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
    LoadStringW(hInstance, IDC_WINAPIBITMAP, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPIBITMAP));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPIBITMAP));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPIBITMAP);
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

   btnPlayAnimation = CreateWindow(L"BUTTON", L"Animation", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 2, 2, 100, 30, hWnd, (HMENU)idBtnPlayAnimation, hInstance, 0);
   btnMetafile = CreateWindow(L"BUTTON", L"Metafile", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE, 105, 2, 100, 30, hWnd, (HMENU)idBtnMetafile, hInstance, 0);

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
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case idBtnPlayAnimation:
            {
                isPlayingAnimation = !isPlayingAnimation;
                isPlayingMetafile = false;
                if (isPlayingAnimation) {
                    // загрузка картинок
                    hBliss = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BLISS));
                    hMower = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_MOWER));

                    timerTick = 0; // обнулить таймер
                    SetTimer(hWnd, idTimer, 33, (TIMERPROC)NULL); // таймер с периодом 33мс
                    clientHDC = GetDC(hWnd); // контекст - клиентская область
                    blissHDC = CreateCompatibleDC(clientHDC); // совместимый контекст в памяти
                    SelectObject(blissHDC, hBliss); // выбор карты в контекст в памяти

                    mowerHDC = CreateCompatibleDC(clientHDC);
                    SelectObject(mowerHDC, hMower);

                }
                else {
                    // освобождаем ресурсы
                    DeleteDC(blissHDC);
                    DeleteObject(hBliss);
                    
                    DeleteDC(mowerHDC);
                    DeleteObject(hMower);
                    
                    ReleaseDC(hWnd, clientHDC);
                    KillTimer(hWnd, idTimer); // остановить таймер
                    InvalidateRect(hWnd, NULL, true);
                }
                
            }
            break;
            case idBtnMetafile: 
            {
                // освобождаем ресурсы, если проигрывали анимацию
                if (isPlayingAnimation) {
                    DeleteDC(blissHDC);
                    DeleteObject(hBliss);

                    DeleteDC(mowerHDC);
                    DeleteObject(hMower);

                    ReleaseDC(hWnd, clientHDC);
                    KillTimer(hWnd, idTimer); // остановить таймер
                    isPlayingAnimation = false;
                }
                
                isPlayingMetafile = !isPlayingMetafile;
                // затирание всего - иначе останется все, что использовалось в анимации
                InvalidateRect(hWnd, NULL, true);
                UpdateWindow(hWnd);
                if (isPlayingMetafile){
                    
                    
                    HDC hdc = CreateMetaFile(NULL);

                    // Рисуем скругленный прямоугольник случайным цветом
                    SelectObject(hdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
                    int xr = 200, yr = 250;
                    RoundRect(hdc, xr, yr, xr + 100, yr + 100, 50, 50);

                    // Рисуем эллипс серой кистью
                    SelectObject(hdc, GetStockObject(LTGRAY_BRUSH));
                    Ellipse(hdc, xr + 100, yr + 100, xr + 350, yr + 250);

                    // Рисуем облако из четырех полукругов с диагональной штриховкой
                    SelectObject(hdc, CreateHatchBrush(HS_FDIAGONAL, RGB(255, 0, 255)));
                    int _size = 70, d1 = 3 * _size, d2 = 2 * _size;
                    int x = 500, y = 250;
                    Chord(hdc, x, y, x + d1, y + d2, x + d1, y + d2 / 2, x, y + d2 / 2);
                    int dx = _size;
                    Chord(hdc, x, y + d2 / 4, x + dx, y + 3 * d2 / 4, x, y + d2 / 2, x + d1, y + d2 / 2);
                    Chord(hdc, x + dx, y + d2 / 4, x + 2 * dx, y + 3 * d2 / 4, x, y + d2 / 2, x + d1, y + d2 / 2);
                    Chord(hdc, x + 2 * dx, y + d2 / 4, x + 3 * dx, y + 3 * d2 / 4, x, y + d2 / 2, x + d1, y + d2 / 2);
                    HMETAFILE hmf = CloseMetaFile(hdc);
                    hdc = GetDC(hWnd);
                    PlayMetaFile(hdc, hmf);
                    CopyMetaFile(hmf, L"metafile.wmf");
                    DeleteMetaFile(hmf);
                }
            }
            break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_TIMER:
    {
        if (isPlayingAnimation) {
            ++timerTick;
        }

    }
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            if (isPlayingAnimation) {
                RECT rect;
                GetWindowRect(hWnd, &rect); // размер окна для растяжения
                StretchBlt(clientHDC, 0, 40, rect.right - rect.left, rect.bottom - rect.top - 40, blissHDC, 0, 0, 800, 600, SRCCOPY);

                int mowerX = rect.right - rect.left - timerTick * 5;
                int mowerY = rect.bottom - rect.top - 400;
                TransparentBlt(clientHDC, mowerX, mowerY, 400, 256, mowerHDC, 0, 0, 893, 574, RGB(0, 0, 0));
                if (mowerX + 400 < 0) timerTick = 0;

            }
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
