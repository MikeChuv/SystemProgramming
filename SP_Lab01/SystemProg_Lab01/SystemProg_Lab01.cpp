// SystemProg_Lab01.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "SystemProg_Lab01.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;								// текущий экземпляр (дескриптор приложения)
WCHAR szTitle[MAX_LOADSTRING];					// Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];			// имя класса главного окна (название оконного класса приложения)

// пункт 4 лабораторной работы
HWND btnLeft;		// кнопка слева (у нее меняем родителя в 6)
HWND btnRight;		// кнопка справа
HWND editText;		// поле ввода (EDIT)
HWND staticText;	// поле вывода (STATIC) 

const static int idBtnLeft = 1;
const static int idBtnRight = 2;
const static int idEditText = 3;
const static int idStaticText = 4;

const static int idTimer = 5; // идентификатор таймера
static int timerTick = 0; // счетчик тиков

int mWindowWidth = 400;
int mWindowHeight = 300;


// Отправить объявления функций, включенных в этот модуль кода:
ATOM				MyRegisterClass(HINSTANCE hInstance);	// функция регистрации класса окна
BOOL				InitInstance(HINSTANCE, int);			// Инициализация экземпляра приложения
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);		// Окно о программе
void				mWindowRecombineRgn(HWND);

// Точка входа в приложение
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,			// Дескриптор экземпляра приложения
					 _In_opt_ HINSTANCE hPrevInstance,	// Дескриптор предыдущего экземпляра приложения
					 _In_ LPWSTR	lpCmdLine,			// Передача командной строки (??) указатель на командную строку, если приложение так запущено 
					 _In_ int		nCmdShow)			// Установки для окна (нормальное, на весь экран и тп + CLI?)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Разместите код здесь.

	// Инициализация глобальных строк (загрузка ресурсов)
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_SYSTEMPROGLAB01, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance); // регистрируем класс окна

	// Выполнить инициализацию приложения:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	// загрузка таблицы акселераторов
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SYSTEMPROGLAB01));

	MSG msg;

	// Цикл основного сообщения:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg); // перевод сообщений клавиш в символьные сообщения
			DispatchMessage(&msg);	// распределение сообщений по оконным процедурам
		}
	}

	return (int) msg.wParam; // возврат последнего сообщения
}



//
//	ФУНКЦИЯ: MyRegisterClass()
//
//	ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex; // структура класса окна для Windows

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;	// стили окна: вертикальная и горизонтальная прокрутки (нужно менять для двойного щелчка)
	wcex.lpfnWndProc	= WndProc; // точка входа в оконную процедуру + обработка сообщений в главном окне
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance; // дескриптор экземпляра приложения
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LAB01ICON)); // загрузка иконки приложения (для проводника, например)
	wcex.hCursor		= LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCEW(IDC_SYSTEMPROGLAB01); // загрузка меню (можно готовить заранее в виде пунктов меню)
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_LAB01ICON)); // отображается в углу окна

	return RegisterClassExW(&wcex);
}

void mWindowRecombineRgn(HWND hWnd) {
	HRGN cutRegion, outRegion;
	RECT mWindowRect;
	GetWindowRect(hWnd, &mWindowRect);
	mWindowWidth = mWindowRect.right - mWindowRect.left; // новая ширина окна
	mWindowHeight = mWindowRect.bottom - mWindowRect.top; // новая высота окна
	outRegion = CreateEllipticRgn(0, -mWindowHeight, mWindowWidth, mWindowHeight);
	int r = 30; // радиус вырезанного круга
	cutRegion = CreateEllipticRgn(mWindowWidth - 100 - r, 140 - r, mWindowWidth - 100 + r, 140 + r);
	CombineRgn(cutRegion, cutRegion, outRegion, RGN_XOR);
	SetWindowRgn(hWnd, cutRegion, true);
}

//
//	 ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//	 ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//	 КОММЕНТАРИИ:
//
//		  В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//		  создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	  CW_USEDEFAULT, mWindowWidth, CW_USEDEFAULT, mWindowHeight, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
	  return FALSE;
   }

   
   //SetWindowPos(hWnd, HWND_TOPMOST, 100, 100, mWindowWidth, mWindowHeight, SWP_SHOWWINDOW); // пункт 3 лабораторной работы
   MoveWindow(hWnd, 100, 100, mWindowWidth, mWindowHeight, true); // пункт 3 лабораторной работы
   mWindowRecombineRgn(hWnd);


   btnLeft = CreateWindow(L"BUTTON", L"Left button", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON , 25, 150, 100, 25, hWnd, (HMENU)idBtnLeft, hInstance, NULL);
   btnRight = CreateWindow(L"BUTTON", L"Right button", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 150, 150, 100, 25, hWnd, (HMENU)idBtnRight, hInstance, NULL);
   editText = CreateWindow(L"EDIT", L"I am EDIT", WS_VISIBLE | WS_CHILD | WS_BORDER, 25, 25, 225, 25, hWnd, (HMENU)idEditText, hInstance, NULL);
   staticText = CreateWindow(L"STATIC", L"I am STATIC", WS_VISIBLE | WS_CHILD, 25, 75, 225, 50, hWnd, (HMENU)idStaticText, hInstance, NULL);

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//	ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//	ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//	WM_COMMAND	- обработать меню приложения
//	WM_PAINT	- Отрисовка главного окна
//	WM_DESTROY	- отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		{
			MessageBox(hWnd, L"Window was created", L"Message", MB_OK);
		}
		break;
	case WM_LBUTTONDOWN: // Нажатие на левую кнопку мыши
		{
			SetWindowText(staticText, L"Left mouse button pressed");
		}
		break;
	case WM_RBUTTONDOWN: // Нажатие на правую кнопку мыши
		{
			SetWindowText(staticText, L"Right mouse button pressed");
			KillTimer(hWnd, idTimer);
			if (GetParent(btnLeft) != hWnd) {
				SetParent(btnLeft, hWnd);
				MoveWindow(btnLeft, 25, 150, 100, 25, true);
			}
		}
		break;
	case WM_INITMENUPOPUP: // Сообщение перед раскрытием меню
		{
			SetWindowText(staticText, L"Menu command!");
		}
		break;
	case WM_TIMER:
		{
			++timerTick;
			MoveWindow(btnLeft, timerTick * 2, timerTick, 100, 25, true);
		}
		break;
	case WM_SIZE:
		{
			mWindowRecombineRgn(hWnd);
		}
		break;

	case WM_COMMAND: // сообщение управляющих элементов и от оконного меню
		{
			int wmId = LOWORD(wParam);
			// int wmEvent = HIWORD(wParam);
			// Разобрать выбор в меню:
			switch (wmId)
			{
			case idBtnLeft: // нажатие на левую кнопку - вставляем в STATIC текст из EDIT
				{
					TCHAR editTextContent[MAX_LOADSTRING];
					GetWindowText(editText, editTextContent, MAX_LOADSTRING);
					SetWindowText(staticText, editTextContent);
				}
				break;
			case idBtnRight: // нажатие на правую кнопку - вставляем в STATIC заголовок окна
				{
					TCHAR editTextContent[MAX_LOADSTRING];
					GetWindowText(hWnd, editTextContent, MAX_LOADSTRING);
					SetWindowText(staticText, editTextContent);
				}
				break;
			case IDM_CHANGEPARENT:
				{
					timerTick = 0; // обнулить таймер 
					SetTimer(hWnd, idTimer, 50, (TIMERPROC)NULL); // таймер в окне hWnd с периодом 50мс
					if (GetParent(btnLeft) == hWnd) {	// если в главном окне
						SetParent(btnLeft, NULL);
					}
					else { // где-то еще
						KillTimer(hWnd, idTimer); // остановить таймер
						SetParent(btnLeft, hWnd); // устанавливаем главное окно как родителя
						MoveWindow(btnLeft, 25, 150, 100, 25, true); // перемещаем на старое место
					}
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
	case WM_PAINT: // рисование в оконной части окна - нормальный режим вывода графики (нельзя рисовать в других частях программы)
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: Добавьте сюда любой код прорисовки, использующий HDC...
			EndPaint(hWnd, &ps);
		}
		break;
	case WM_DESTROY:
		MessageBox(hWnd, L"Window was closed", L"Message", MB_OK);
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
