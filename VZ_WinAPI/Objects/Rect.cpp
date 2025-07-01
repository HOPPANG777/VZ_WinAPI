#include "stdafx.h"
#include "Rect.h"

void Rect::Update(float, const RECT&)
{
	if (keyCount == 2) speed = maxSpeed / sqrtf(2.0f);
	else speed = maxSpeed;

	APIFuncs::SetRectCentered(position, scale, rect);
}

void Rect::Render(HDC hdc)
{
	APIFuncs::DrawRect(hdc, rect);
	FillRect(hdc, &rect, brush);
}

bool Rect::CheckIntersect(const Rect& other) const
{
	if 
	(
		rect.left <= other.rect.right &&
		rect.right >= other.rect.left &&
		rect.top <= other.rect.bottom &&
		rect.bottom >= other.rect.top
	)
	return true;
	
	return false;
}

bool Rect::CheckIntersect(const Vector2& position) const
{
	if
	(
		rect.left <= position.x &&
		rect.right >= position.x &&
		rect.top <= position.y &&
		rect.bottom >= position.y
	)
	return true;
	
	return false;
}
