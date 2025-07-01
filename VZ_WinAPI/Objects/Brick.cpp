#include "stdafx.h"
#include "Brick.h"

void Brick::Render(HDC hdc)
{
    if (!active) return;

    APIFuncs::DrawRect(hdc, rect);
    FillRect(hdc, &rect, brickBrush);
}