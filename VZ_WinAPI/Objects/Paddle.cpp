#include "stdafx.h"
#include "Paddle.h"


void Paddle::Update(float deltaTime, const RECT&)
{
    if (Input::Get()->Press(VK_LEFT)) position.x -= speed * deltaTime;
    if (Input::Get()->Press(VK_RIGHT)) position.x += speed * deltaTime;

    // 필요에 따라 화면 경계 체크를 추가하세요.

    APIFuncs::SetRectCentered(position, size, rect);
}

void Paddle::Render(HDC hdc)
{
    APIFuncs::DrawRect(hdc, rect);
    FillRect(hdc, &rect, rectBrush);
}
