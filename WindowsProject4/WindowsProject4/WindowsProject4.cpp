// WindowsProject1.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//


#include "framework.h"
#include "WindowsProject4.h"
#include "stdio.h"


#define MAX_LOADSTRING 100
#define BOARD_MAX_X 700
#define BOARD_MAX_Y 700
#define BOARD_MIN_X 100
#define BOARD_MIN_Y 100
//#define GAME_SPEED 1

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.


// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
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

	// TODO: 여기에 코드를 입력합니다.

	// 전역 문자열을 초기화합니다.
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINDOWSPROJECT4, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 애플리케이션 초기화를 수행합니다:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT4));

	MSG msg;

	// 기본 메시지 루프입니다:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT4));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(184, 116, 27)); //(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT4);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPED | WS_SYSMENU,
		CW_USEDEFAULT, 0, 1000, 800, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;


}

int kind;
int mc[100][4] = { 0, };
int mc_count;
LPARAM g_lParam;
int direct = 10;
int cur_x, cur_y;
int mirrorkind = 1;
int x, y;
int mc_x, mc_y;
WNDCLASS wndclass;
HPEN my_pen;
HPEN os_pen;
HBRUSH my_brush;
HBRUSH os_brush;
int GAME_SPEED = 1;

int check = -1;

int mirrorL_x, mirrorL_y, mirrorR_x, mirrorR_y;

INT GamesetCheck(int laser_x, int laser_y) {
	if (laser_x > BOARD_MAX_X || laser_y > BOARD_MAX_Y || laser_x < BOARD_MIN_X || laser_y < BOARD_MIN_Y)
		return 0;
	else if (laser_x > 100 && laser_x < 400 && laser_y>200 && laser_y < 300)
		return 1;
	else if (laser_x > 200 && laser_x < 600 && laser_y>400 && laser_y < 500)
		return 1;
	else if (laser_x > 500 && laser_x < 600 && laser_y>100 && laser_y < 400)
		return 1;
	else if (laser_x > 600 && laser_x < 700 && laser_y>100 && laser_y < 200)
		return 1;
	else if (laser_x > 100 && laser_x < 300 && laser_y>600 && laser_y < 700)
		return 1;
	else if (laser_x > 400 && laser_x < 500 && laser_y>500 && laser_y < 600)
		return 1;
	else if (laser_x > 600 && laser_x < 700 && laser_y>600 && laser_y < 700)
		return 1;
	else if (laser_x == 700 && laser_y == 250)
		return 2;
}
BOOL MirrorAction(int laser_x, int laser_y) {

	for (int i = 0; i <= 100; i++) {
		if (mc[i][0] == laser_x && mc[i][1] == laser_y) {

			if (mc[i][2] <= mc[i][3] && direct == 10) {
				direct = 20;
				return true;
			}
			if (mc[i][2] >= mc[i][3] && direct == 10) {
				direct = 40;
				return true;
			}
			if (mc[i][2] <= mc[i][3] && direct == 20) {
				direct = 10;
				return true;
			}
			if (mc[i][2] >= mc[i][3] && direct == 20) {
				direct = 30;
				return true;
			}
			if (mc[i][2] <= mc[i][3] && direct == 30) {
				direct = 40;
				return true;
			}
			if (mc[i][2] >= mc[i][3] && direct == 30) {
				direct = 20;
				return true;
			}
			if (mc[i][2] <= mc[i][3] && direct == 40) {
				direct = 30;
				return true;
			}
			if (mc[i][2] >= mc[i][3] && direct == 40) {
				direct = 10;
				return true;
			}

		}
		else
			continue;
	}
	return false;
}


/*INT Refract() {
   if (direct == 10 && left_y > right_y)
	  return 40;
   if (direct == 10 && left_y < right_y)
	  return 20;
   if (direct == 20 && left_y > right_y)
	  return 30;
   if (direct == 20 && left_y < right_y)
	  return 10;
   if (direct == 30 && left_y > right_y)
	  return 20;
   if (direct == 30 && left_y < right_y)
	  return 40;
   if (direct == 40 && left_y > right_y)
	  return 10;
   if (direct == 40 && left_y < right_y)
	  return 30;
}*/

DWORD WINAPI laser(LPVOID param)
{
	HWND hWnd = (HWND)param;
	int i, j;
	HDC hdc;
	cur_x = 100;
	cur_y = 150;
	hdc = GetDC(hWnd);
	my_pen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	os_pen = (HPEN)SelectObject(hdc, my_pen);
	while (true) {

		switch (direct)
		{
		case 10:
		{
			for (i = cur_x + GAME_SPEED; i < 1500; i += GAME_SPEED) {
				if (direct != 10)
					break;
				MoveToEx(hdc, cur_x, cur_y, NULL);
				LineTo(hdc, i, cur_y);
				Sleep(1);
				cur_x = i;
				if (MirrorAction(cur_x, cur_y)) {
					//direct = Refract(mirrorL_y, mirrorR_y);
					break;
				}
				kind = GamesetCheck(cur_x, cur_y);
				if (kind == 0 || kind == 1) {
					MessageBox(hWnd, L"Game Over", L"Game Over", MB_OK);
					ExitThread(0);
				}
				else if (kind == 2) {
					MessageBox(hWnd, L"Clear", L"Clear", MB_OK);
					ExitThread(0);
				}

			}
		}
		break;
		case 20:
		{

			for (j = cur_y + GAME_SPEED; j < 1500; j += GAME_SPEED) {
				if (direct != 20)
					break;
				MoveToEx(hdc, cur_x, cur_y, NULL);
				LineTo(hdc, cur_x, j);
				Sleep(1);
				cur_y = j;
				if (MirrorAction(cur_x, cur_y)) {
					//direct = Refract(mirrorL_y, mirrorR_y);
					break;
				}
				kind = GamesetCheck(cur_x, cur_y);
				if (kind == 0 || kind == 1) {
					MessageBox(hWnd, L"Game Over", L"Game Over", MB_OK);
					ExitThread(0);
				}
				else if (kind == 2) {
					MessageBox(hWnd, L"Clear", L"Clear", MB_OK);
					ExitThread(0);
				}

			}
		}
		break;
		case 30:
		{
			for (i = cur_x - GAME_SPEED; i < 1500; i -= GAME_SPEED) {
				if (direct != 30)
					break;
				MoveToEx(hdc, cur_x, cur_y, NULL);
				LineTo(hdc, i, cur_y);
				Sleep(1);
				cur_x = i;
				if (MirrorAction(cur_x, cur_y)) {
					//direct = Refract(mirrorL_y, mirrorR_y);
					break;
				}
				kind = GamesetCheck(cur_x, cur_y);
				if (kind == 0 || kind == 1) {
					MessageBox(hWnd, L"Game Over", L"Game Over", MB_OK);
					ExitThread(0);
				}
				else if (kind == 2) {
					MessageBox(hWnd, L"Clear", L"Clear", MB_OK);
					ExitThread(0);
				}
			}
		}
		break;
		case 40:
		{
			for (j = cur_y - GAME_SPEED; j < 1500; j -= GAME_SPEED) {
				if (direct != 40)
					break;
				MoveToEx(hdc, cur_x, cur_y, NULL);
				LineTo(hdc, cur_x, j);
				Sleep(1);
				cur_y = j;
				if (MirrorAction(cur_x, cur_y)) {
					//direct = Refract(mirrorL_y, mirrorR_y);
					break;
				}
				kind = GamesetCheck(cur_x, cur_y);
				if (kind == 0 || kind == 1) {
					MessageBox(hWnd, L"Game Over", L"Game Over", MB_OK);
					ExitThread(0);
				}
				else if (kind == 2) {
					MessageBox(hWnd, L"Clear", L"Clear", MB_OK);
					ExitThread(0);
				}

			}
		}
		break;
		}
	}
	SelectObject(hdc, os_pen);
	DeleteObject(my_pen);
	ReleaseDC(hWnd, hdc);
	ExitThread(0);
	return 0;
}



//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
HINSTANCE g_hinst;
HWND btn1_button;
HINSTANCE g_hinst2;
HWND btn1_button2;
//
//
HANDLE g_hdl[3000] = { NULL, };
int g_index = 0;


HDC hdc;
int num = 0;
int k=0;


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		HWND btn1_button = CreateWindow(L"button", L"START", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			20, 20, 100, 25, hWnd, (HMENU)0x1001, g_hinst, NULL);
		HWND btn1_button2 = CreateWindow(L"button", L"RESET", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			140, 20, 100, 25, hWnd, (HMENU)0x1002, g_hinst, NULL);
	}
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 메뉴 선택을 구문 분석합니다:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case 0x1001:
		{
			k = 1;
			//MessageBox(hWnd, L"클릭됨", L"버튼", MB_OK);
			DWORD tid = 0;
			g_lParam = lParam;
			g_hdl[g_index++] = CreateThread(NULL, 0, laser, hWnd, 0, &tid);

			if (NULL == g_hdl) {
				MessageBox(hWnd, L"실패", L"실패", MB_OK);
				break;
			}

		}
		break;
		case 0x1002:
		{
			k = 0;
			mirrorkind = 1;
			InvalidateRect(hWnd, NULL, TRUE);
			direct = 10;
			for (int i = 0; i <= 100; i++) {
				for (int j = 0; j <= 4; j++) {
					mc[i][j] = 0;
				}
			}
		}
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}


	}
	break;
	case WM_LBUTTONDOWN:
	{
		if (k != 1) {
			MessageBox(hWnd, L"시작 전에는 거울을 배치할 수 없습니다.", L"!", MB_OK);
			break;
		}
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		if (x < BOARD_MIN_X || x > BOARD_MAX_X || y < BOARD_MIN_Y || y > BOARD_MAX_Y ||
			(x > 100 && x < 400 && y>200 && y < 300) || (x > 200 && x < 600 && y>400 && y < 500) ||
			(x > 500 && x < 600 && y>100 && y < 400) || (x > 600 && x < 700 && y>100 && y < 200) ||
			(x > 100 && x < 300 && y>600 && y < 700) || (x > 400 && x < 500 && y>500 && y < 600) ||
			(x > 600 && x < 700 && y>600 && y < 700)) {
			MessageBox(hWnd, L"거울을 배치할 수 없는 곳입니다.", L"!", MB_OK);
			break;
		}
		hdc = GetDC(hWnd);
		switch (mirrorkind)
		{
		case 1:
		{

			my_pen = CreatePen(PS_SOLID, 3, RGB(135, 206, 235));
			os_pen = (HPEN)SelectObject(hdc, my_pen);


			x = (x / 100) * 100;
			y = (y / 100) * 100;

			for (int i = 0; i <= 100; i++) {
				if (x + 50 == mc[i][0] && y + 50 == mc[i][1]) {
					MessageBox(hWnd, L"이미 거울이 배치된 곳입니다..", L"!", MB_OK);
					break;
				}
				else {
					MoveToEx(hdc, x + 30, y + 30, NULL);
					LineTo(hdc, x + 70, y + 70);

					SelectObject(hdc, os_pen);
					DeleteObject(my_pen);
					ReleaseDC(hWnd, hdc);
					mirrorL_x = x;
					mirrorL_y = y;
					mirrorR_x = x + 100;
					mirrorR_y = y + 100;
				}
			}
		}
		break;
		case 2:
		{
			my_pen = CreatePen(PS_SOLID, 2, RGB(135, 206, 235));
			os_pen = (HPEN)SelectObject(hdc, my_pen);
			x = (x / 100) * 100;
			y = (y / 100) * 100;

			for (int i = 0; i <= 100; i++) {
				if (x + 50 == mc[i][0] && y + 50 == mc[i][1]) {
					MessageBox(hWnd, L"이미 거울이 배치된 곳입니다..", L"!", MB_OK);
					break;
				}
				else {
					MoveToEx(hdc, x + 70, y + 30, NULL);
					LineTo(hdc, x + 30, y + 70);

					SelectObject(hdc, os_pen);
					DeleteObject(my_pen);
					ReleaseDC(hWnd, hdc);

					mirrorL_x = x;
					mirrorL_y = y + 100;
					mirrorR_x = x + 100;
					mirrorR_y = y;
				}
			}


		}
		break;
		}
		mc_x = x + 50;
		mc_y = y + 50;
		mc[num][0] = mc_x;
		mc[num][1] = mc_y;
		mc[num][2] = mirrorL_y;
		mc[num][3] = mirrorR_y;
		num = num + 1;

	}
	break;
	case WM_RBUTTONDOWN:
	{
		/*direct++;
		if (direct > 4)
		   direct = 1;*/
		mirrorkind += 1;
		if (mirrorkind > 2)
			mirrorkind = 1;

		hdc = GetDC(hWnd);

		switch (mirrorkind)
		{
		case 1:
		{
			my_brush = CreateSolidBrush(RGB(244, 176, 87));
			os_brush = (HBRUSH)SelectObject(hdc, my_brush);
			Rectangle(hdc, 850, 150, 950, 250);
			SelectObject(hdc, os_brush);
			DeleteObject(my_brush);
			my_pen = CreatePen(PS_SOLID, 2, RGB(135, 206, 235));
			os_pen = (HPEN)SelectObject(hdc, my_pen);

			MoveToEx(hdc, 880, 180, NULL);
			LineTo(hdc, 920, 220);
			SelectObject(hdc, os_pen);
			DeleteObject(my_pen);
		}
		break;
		case 2:
		{
			my_brush = CreateSolidBrush(RGB(244, 176, 87));
			os_brush = (HBRUSH)SelectObject(hdc, my_brush);
			Rectangle(hdc, 850, 150, 950, 250);
			SelectObject(hdc, os_brush);
			DeleteObject(my_brush);
			my_pen = CreatePen(PS_SOLID, 2, RGB(135, 206, 235));
			os_pen = (HPEN)SelectObject(hdc, my_pen);
			MoveToEx(hdc, 920, 180, NULL);
			LineTo(hdc, 880, 220);
			SelectObject(hdc, os_pen);
			DeleteObject(my_pen);
		}
		break;
		}
		ReleaseDC(hWnd, hdc);

	}
	break;
	case WM_KEYDOWN: {
		switch (wParam) {
		case VK_UP: {
			//MessageBox(hWnd, L"up..", L"!", MB_OK);
			switch(GAME_SPEED) {
			case 1: {
				GAME_SPEED = 2;
			}
			break;

			case 2: {
				GAME_SPEED = 5;
			}
			break;

			
			}
		}
		break;
		case VK_DOWN: {
			//MessageBox(hWnd, L"down..", L"!", MB_OK);
			switch (GAME_SPEED) {
			
			case 5: {
				GAME_SPEED = 2;
			}
			break;
			case 2: {
				GAME_SPEED = 1;
			}
			break;
			}
		}
		break;
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		// Device Context : 출력을 위한 모든 데이터를 가지는 구조체
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...


		// 위치를 옮기고 라인을 그린다.



		SetBkMode(hdc, TRANSPARENT);

		TextOut(hdc, 850, 130, TEXT("현재 거울"), lstrlen(TEXT("현재 거울")));
		TextOut(hdc, 720, 245, TEXT("GOAL"), lstrlen(TEXT("GOAL")));
		TextOut(hdc, 35, 145, TEXT("START"), lstrlen(TEXT("START")));
		TextOut(hdc, 820, 460, TEXT("조작법"), lstrlen(TEXT("조작법")));
		TextOut(hdc, 750, 480, TEXT("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ"), lstrlen(TEXT("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ")));
		TextOut(hdc, 750, 500, TEXT("마우스 좌클릭 : 거울 배치"), lstrlen(TEXT("마우스 좌클릭 : 거울 배치")));
		TextOut(hdc, 750, 520, TEXT("마우스 우클릭 : 거울 변경"), lstrlen(TEXT("마우스 우클릭 : 거울 변경")));

		my_brush = CreateSolidBrush(RGB(244, 176, 87));
		os_brush = (HBRUSH)SelectObject(hdc, my_brush);
		Rectangle(hdc, 850, 150, 950, 250);
		Rectangle(hdc, BOARD_MIN_X, BOARD_MIN_Y, BOARD_MAX_X, BOARD_MAX_Y);


		SelectObject(hdc, os_brush);
		DeleteObject(my_brush);


		my_pen = CreatePen(PS_SOLID, 2, RGB(135, 206, 235));
		os_pen = (HPEN)SelectObject(hdc, my_pen);
		MoveToEx(hdc, 880, 180, NULL);
		LineTo(hdc, 920, 220);
		SelectObject(hdc, os_pen);
		DeleteObject(my_pen);

		my_brush = CreateSolidBrush(RGB(255, 0, 0));
		os_brush = (HBRUSH)SelectObject(hdc, my_brush);
		Rectangle(hdc, 80, 100, 100, 200);
		SelectObject(hdc, os_brush);
		DeleteObject(my_brush);

		my_brush = CreateSolidBrush(RGB(0, 255, 0));
		os_brush = (HBRUSH)SelectObject(hdc, my_brush);
		Rectangle(hdc, 700, 200, 720, 300);
		SelectObject(hdc, os_brush);
		DeleteObject(my_brush);

		my_brush = CreateSolidBrush(RGB(0, 0, 0));
		os_brush = (HBRUSH)SelectObject(hdc, my_brush);


		Rectangle(hdc, 200, 400, 600, 500);
		Rectangle(hdc, 100, 600, 300, 700);
		Rectangle(hdc, 400, 500, 500, 600);
		Rectangle(hdc, 500, 100, 600, 400);
		Rectangle(hdc, 600, 100, 700, 200);
		Rectangle(hdc, 600, 600, 700, 700);
		Rectangle(hdc, 100, 200, 400, 300);

		SelectObject(hdc, os_brush);
		DeleteObject(my_brush);

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

// 정보 대화 상자의 메시지 처리기입니다.
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