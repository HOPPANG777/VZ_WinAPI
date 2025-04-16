#include "stdafx.h"
#include "APIFuncs.h"

void APIFuncs::SetRect(const int x, const int y, const int width, const int height, RECT& rect)
{
	rect = { x, y, x + width, y + height };
}

void APIFuncs::SetRect(const Vector2& position, const Vector2& scale, RECT& rect)
{
	rect = { LONG(position.x), LONG(position.y), LONG(position.x + scale.x), LONG(position.y + scale.y) };
}

void APIFuncs::SetRectCentered(const int x, const int y, const int width, const int height, RECT& rect)
{
	rect = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };
}

void APIFuncs::SetRectCentered(const Vector2& position, const Vector2& scale, RECT& rect)
{
	rect = { LONG(position.x - (scale.x * 0.5f)), LONG(position.y - (scale.y * 0.5f)),
		LONG(position.x + (scale.x * 0.5f)), LONG(position.y + (scale.y * 0.5f)) };
}

void APIFuncs::DrawLine(const HDC& hdc, const int x1, const int y1, const int x2, const int y2)
{
	MoveToEx(hdc, x1, y1, nullptr);
	LineTo(hdc, x2, y2);
}

void APIFuncs::DrawLine(const HDC& hdc, const RECT& r)
{
	MoveToEx(hdc, r.left, r.top, nullptr);
	LineTo(hdc, r.right, r.bottom);
}

void APIFuncs::DrawRect(const HDC& hdc, const int x, const int y, const int width, const int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

void APIFuncs::DrawRect(const HDC& hdc, const RECT& r)
{
	Rectangle(hdc, r.left, r.top, r.right, r.bottom);
}

void APIFuncs::DrawCircle(const HDC& hdc, const int x, const int y, const int width, const int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

void APIFuncs::DrawCircle(const HDC& hdc, const RECT& r)
{
	Ellipse(hdc, r.left, r.top, r.right, r.bottom);
}
