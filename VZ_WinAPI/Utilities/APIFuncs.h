#pragma once

#include "Vector.h"

class APIFuncs
{
public:
	static void SetRect(const int x, const int y, const int width, const int height, RECT& rect);
	static void SetRect(const Vector2& position, const Vector2& scale, RECT& rect);
	static void SetRectCentered(const int x, const int y, const int width, const int height, RECT& rect);
	static void SetRectCentered(const Vector2& position, const Vector2& scale, RECT& rect);

public:
	static void DrawLine(const HDC& hdc, const int x1, const int y1, const int x2, const int y2);
	static void DrawLine(const HDC& hdc, const RECT& r);

public:
	static void DrawRect(const HDC& hdc, const int x, const int y, const int width, const int height);
	static void DrawRect(const HDC& hdc, const RECT& r);

public:
	static void DrawCircle(const HDC& hdc, const int x, const int y, const int width, const int height);
	static void DrawCircle(const HDC& hdc, const RECT& r);

};