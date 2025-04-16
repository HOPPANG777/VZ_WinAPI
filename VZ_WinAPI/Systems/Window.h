#pragma once

#include "Program.h"
#include "Input.h"
#include "Time.h"

struct WinDesc
{
	std::wstring appName = L"";
	HINSTANCE instance = nullptr;
	HWND handle = nullptr;
	float width = 0.0f;
	float height = 0.0f;
};

class Window
{
public:
	Window(const WinDesc& initDesc);
	~Window();

public:
	ATOM MyRegisterClass(const WinDesc& desc);

	WPARAM Run();

private:
	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);

	WinDesc desc;

	static std::unique_ptr<class Program> program;
};