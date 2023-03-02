#include <windows.h>

LRESULT CALLBACK MainWinProc(HWND, UINT, WPARAM, LPARAM);
#define ID_MYBUTTON 1    /* идентификатор для кнопочки внутри главного окна */

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int ss) {
	/* создаем и регистрируем класс главного окна */
	WNDCLASS wc;
	wc.style = 0; //Стиль окна
	wc.lpfnWndProc = MainWinProc; //Указатель на оконную процедуру
	wc.cbClsExtra = wc.cbWndExtra = 0; //Устанавливает число дополнительных 
	//байтов, которые размещаются вслед за экземпляром окна
	wc.hInstance = hInst; //Дескриптор экземпляра, который содержит оконную процедуру для класса.
	wc.hIcon = NULL;//Дескриптор значка класса. Этот член структуры должен быть дескриптором ресурса значка. 
	wc.hCursor = NULL; //Дескриптор курсора класса. Этот член структуры должен быть дескриптором ресурса курсора. 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); //hbrBackground
	/*
	Дескриптор кисти фона класса. Этот член структуры может быть дескриптором физической кисти, 
	которая используется, чтобы красить цветом фона, или это может быть кодом цвета. 
	Код цвета должен быть одним из ниже перечисленных стандартных системных цветов 
	(значение 1 должно добавляться к выбранному цвету). 
	Если дается код цвета, Вы должны преобразовать его в один из ниже перечисленных типов 
	*/
	wc.lpszMenuName = NULL; 
	/*
	Указатель на символьную строку с символом конца строки ('\0') (нуль-терминатором), 
	которая устанавливает имя ресурса меню класса, которое как имя показывается в файле ресурса*/
	wc.lpszClassName = L"Win32 Object";
	/*
	Если символьная строка, она задает имя класса окна.*/
	if (!RegisterClass(&wc)) return FALSE;

	/* создаем главное окно и отображаем его */
	HWND hMainWnd = CreateWindow(L"Win32 Object", L"Win32 приложение", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInst, NULL);
	if (!hMainWnd) return FALSE;
	ShowWindow(hMainWnd, ss);
	UpdateWindow(hMainWnd);

	MSG msg; /* цикл обработки событий */
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

/* процедура обработки сообщений для главного окна */
LRESULT CALLBACK MainWinProc(HWND hw, UINT msg, WPARAM wp, LPARAM lp) {
	RECT Size;
	GetWindowRect(hw, &Size);
	int sizeW = 100;
	int sizeH = 20;
	int x = (Size.right - Size.left - sizeW) / 2;
	int y = (Size.bottom - Size.top - sizeH)/2;
	int x1 = (Size.right - Size.left - sizeW - 200) / 2;
	int y1 = (Size.bottom - Size.top - sizeH) / 2;
	HWND nBtn1;
	HWND nBtn2;
	HWND hStatic;
	HWND hEdit;
	switch (msg) {
	case WM_CREATE:

		/* при создании окна внедряем в него кнопочку */
		nBtn1 = CreateWindow(L"button", L"OK", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
			x, y, sizeW, sizeH, hw, (HMENU)ID_MYBUTTON, NULL, NULL);
		/* стиль WS_CHILD означает, что это дочернее окно и для него
		 вместо дескриптора меню будет передан целочисленный идентификатор,
		 который будет использоваться дочерним окном для оповещения
		 родительского окна через WM_COMMAND */
		nBtn2 = CreateWindow(L"button", L"Не ОК", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
			x1, y1, sizeW, sizeH, hw, (HMENU)(ID_MYBUTTON + 1), NULL, NULL);

		hStatic = CreateWindow(L"static", L"Мой текст", WS_CHILD | WS_VISIBLE,
			300, 300, 150, 20, hw, NULL, NULL, NULL);

		hEdit = CreateWindow(L"edit", L"Мой редактируемый текст", WS_CHILD | WS_VISIBLE,
			500, 300, 200, 20, hw, NULL, NULL, NULL);


		return 0;
	case WM_COMMAND:
		/* нажата наша кнопочка? */
		if ((HIWORD(wp) == 0) && (LOWORD(wp) == ID_MYBUTTON))
			MessageBox(hw, L"Нажата кнопка", L"MessageBox", MB_OK | MB_ICONWARNING);
		if ((HIWORD(wp) == 0) && (LOWORD(wp) == ID_MYBUTTON + 1))
			MessageBox(hw, L"Нажата кнопка 2", L"MessageBox", MB_OK | MB_ICONWARNING);
		return 0;
	case WM_DESTROY:
		/* пользователь закрыл окно, программа может завершаться */
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hw, msg, wp, lp);
}

/*
https://learn.microsoft.com/ru-ru/windows/win32/api/winuser/nf-winuser-createwindowa

COLOR_ACTIVEBORDER
COLOR_ACTIVECAPTION
COLOR_APPWORKSPACE
COLOR_BACKGROUND
COLOR_BTNFACE
COLOR_BTNSHADOW
COLOR_BTNTEXT
COLOR_CAPTIONTEXT
COLOR_GRAYTEXT
COLOR_HIGHLIGHT
COLOR_HIGHLIGHTTEXT
COLOR_INACTIVEBORDER
COLOR_INACTIVECAPTION
COLOR_MENU
COLOR_MENUTEXT
COLOR_SCROLLBAR
COLOR_WINDOW
COLOR_WINDOWFRAME
COLOR_WINDOWTEXT
*/

/*
typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int UINT;
typedef int INT;
typedef long BOOL;
#define FALSE 0
#define TRUE 1
typedef long LONG;
typedef unsigned long DWORD;
typedef void *LPVOID;
typedef char CHAR;
typedef CHAR *LPSTR;
typedef const CHAR *LPCSTR;
*/