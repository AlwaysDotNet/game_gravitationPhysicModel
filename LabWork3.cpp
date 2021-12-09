#include "CBallsArray.h"
#include "CBallsSettingsMonitor.h"
#include <time.h>
#include "CTrap.h"
#define VK_G 0x47
//Точка входа для Windows приложение
HINSTANCE g_hInstance;

HWND g_mainWnd;
int g_nCmdShow;

RECT g_rectWind;
DWORD g_Prev_FrameTime;

CBallsArray balls(50);
CBallsSettingsMonitor monitor;

BOOL g_isGrav=FALSE;


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL InitAppClass();
BOOL InitWindow();
WPARAM StartMessageLoop();
void OnIdle();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand(time(0));
	g_hInstance = hInstance;
	g_nCmdShow = nCmdShow;
	if (!InitAppClass())
		return 0;
	if (!InitWindow())
		return 0;
	
	g_Prev_FrameTime = GetTickCount();

	GetClientRect(g_mainWnd, &g_rectWind);

	
	
	return StartMessageLoop();
}
//Регистрация класс окно приложение
BOOL InitAppClass()
{
	ATOM class_id;//Идентификатор
	WNDCLASS wc;//Обект  класса окно приложени
	memset(&wc, 0, sizeof(wc));
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = g_hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszClassName = L"LabWork2";
	//Регистрация класс
	class_id = RegisterClass(&wc);
	if (class_id != 0)
		return TRUE;
	return FALSE;

}
BOOL InitWindow()
{
	g_mainWnd = CreateWindow(L"LabWork2", L"Лабораторная работа № 2", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		500, 500, 0, 0, g_hInstance, 0);
	//Если окно не создано
	if (!g_mainWnd)
		return FALSE;
	ShowWindow(g_mainWnd, g_nCmdShow);
	UpdateWindow(g_mainWnd);
	return TRUE;
}
//Обработка сообщение
WPARAM StartMessageLoop()
{
	MSG msg;
	while (1)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;
			DispatchMessage(&msg);
		}
		else
		{
			Sleep(20);
			OnIdle();
		}
	}
	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_SIZE:
	{
		g_rectWind.top = 0;
		g_rectWind.left = 0;
		g_rectWind.bottom = HIWORD(lParam);
		g_rectWind.right = LOWORD(lParam);
		balls.SetBounds(g_rectWind);
		return 0;
	}
	//Обработка  нажатие клавиш ->
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_DOWN:
			monitor.SpeedDown();
			return 0;
		case VK_UP:
			monitor.SpeedUp();
		case VK_LEFT:
			monitor.AngleUp();
			return 0;
		case VK_RIGHT:
			monitor.AngleDown();
			return 0;
		case VK_G:
			if (g_isGrav)
				g_isGrav = FALSE;
			else
				g_isGrav = TRUE;
			return 0;
		default:
			break;
		}
		break;
	}
	//Отрисовка
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC dc;
		dc = BeginPaint(g_mainWnd, &ps);
		balls.Draw(dc);
		monitor.Draw(dc);
		if (g_isGrav)
			TextOut(dc, 35, 5, L"Гравитация включена", 19);
		else
			TextOut(dc, 35, 5, L"Гравитация отключено", 20);
		balls.trap->Draw(dc);
		EndPaint(g_mainWnd, &ps);
		return 0;
	}
	case WM_LBUTTONUP:
	{
		double xpos = GET_X_LPARAM(lParam);
		double ypos = GET_Y_LPARAM(lParam);
		CBall* bal = balls.Add();
		if (bal != NULL)
		{
			double vx, vy;
			monitor.GetVxVy(vx, vy);
			bal->SetParams(xpos, ypos, 12,vx,vy, g_rectWind);
		}

		return 0;
	}
	//Добавление цветовых шариков при шелчке прваой кнопки мышки (при отпускание)
	case WM_RBUTTONDOWN:
	{
		double xpos = GET_X_LPARAM(lParam);
		double ypos = GET_Y_LPARAM(lParam);
		CColoredBall* bal=balls.AddColoredBall();
		if (bal != NULL)
		{
			double vx, vy;
			monitor.GetVxVy(vx, vy);
			bal->SetParams(xpos, ypos, 12, vx, vy,g_rectWind);
			bal->SetColor(rand() % 256, rand() % 256, rand() % 256);

		}
		return 0;
	}
	default:
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
void OnIdle()
{
	DWORD cur_time = GetTickCount();
	DWORD delta_time = cur_time - g_Prev_FrameTime;
	//Гравитация
	if (g_isGrav)
	{
		balls.SetGravityFactor(1.0);
	}
	else
		balls.SetGravityFactor(0.0);
	//Перемешение
	balls.Move(delta_time);
	g_Prev_FrameTime = cur_time;
	InvalidateRect(g_mainWnd, NULL, TRUE);
}