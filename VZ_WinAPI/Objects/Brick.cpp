#include "stdafx.h"
#include "Brick.h"

void Brick::Update(float, const RECT&)
{
    // 벽돌은 특별한 업데이트 로직이 없다.
}

void Brick::Render(HDC hdc)
{
    if (!active) return;

    APIFuncs::DrawRect(hdc, rect);
    FillRect(hdc, &rect, brickBrush);
}