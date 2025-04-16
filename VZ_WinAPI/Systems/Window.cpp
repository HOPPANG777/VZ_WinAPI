#include "stdafx.h"
#include "Window.h"

std::unique_ptr<class Program> Window::program = std::make_unique<Program>();

Window::Window(const WinDesc& initDesc)
	: desc(initDesc)
{
	WORD wHr = MyRegisterClass(desc);
	assert(wHr != 0);

	desc.handle = CreateWindowExW
	(
		WS_EX_APPWINDOW,
		desc.appName.c_str(),
		desc.appName.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		nullptr,
		HMENU(nullptr),
		desc.instance,
		nullptr
	);

	RECT rect = { 0, 0, LONG(desc.width), LONG(desc.height) };

	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, 0);

	UINT centerLeft = (GetSystemMetrics(SM_CXSCREEN) - UINT(desc.width)) / 2 + rect.left;
	UINT centerTop = (GetSystemMetrics(SM_CYSCREEN) - UINT(desc.height)) / 2 + rect.top;

	MoveWindow
	(
		desc.handle,
		centerLeft,
		centerTop,
		rect.right - rect.left,
		rect.bottom - rect.top,
		true
	);

	ShowWindow(desc.handle, SW_SHOWNORMAL);

	UpdateWindow(desc.handle);

	ShowCursor(true);
}

Window::~Window()
{
	DestroyWindow(desc.handle);
	UnregisterClassW(desc.appName.c_str(), desc.instance);
}

ATOM Window::MyRegisterClass(const WinDesc& desc)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	wcex.lpfnWndProc = &WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = desc.instance;
	wcex.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = HBRUSH(GetStockObject(GRAY_BRUSH));
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = desc.appName.c_str();
	wcex.hIconSm = wcex.hIcon;

	return RegisterClassExW(&wcex);
}

WPARAM Window::Run()
{
	MSG msg = { 0 };

	// 기본 메시지 루프입니다:
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return msg.wParam;
}

LRESULT Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	Input::Get()->InputProc(message, lParam);
	static POINT mousePos = { 0 };
	static POINT startPos = { 0 };
	static POINT endPos = { 0 };
	static std::wstring mouseStr = L"";

	switch (message)
	{
	case WM_CREATE:
	{
		gHandle = handle;
		SetTimer(handle, 1, USER_TIMER_MINIMUM, nullptr);
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		gHDC = BeginPaint(handle, &ps);
		program->Render(gHDC);

		EndPaint(handle, &ps);
	}
	break;
	case WM_KEYDOWN:
	{

	}
	break;
	case WM_MOUSEMOVE:
	{
		mousePos.x = GET_X_LPARAM(lParam);
		mousePos.y = GET_Y_LPARAM(lParam);
		mouseStr = L"X : " + std::to_wstring(mousePos.x) + L", Y : " + std::to_wstring(mousePos.y);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		startPos = mousePos;
	}
	break;
	case WM_LBUTTONUP:
	{
		endPos = mousePos;
		InvalidateRect(handle, nullptr, true);
	}		
	break;
	case WM_TIMER:
	{
		Input::Get()->Update();
		Time::Get()->Update();

		RECT clientRect;
		GetClientRect(handle, &clientRect);
		program->Update(Time::Get()->GetDeltaTime(), clientRect);
		
		InvalidateRect(handle, nullptr, true);
		UpdateWindow(handle);
	}	
	break;
	case WM_CLOSE:
	{
		KillTimer(handle, 1);
		PostQuitMessage(0);
	}
	break;
	default:
		return DefWindowProc(handle, message, wParam, lParam);
	}
	return 0;
}
