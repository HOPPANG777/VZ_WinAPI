#include "stdafx.h"
#include "Ball.h"

void Ball::Update(float deltaTime, const RECT& windowRect)
{
    position = position + velocity * deltaTime;

    // 좌우 경계 체크
    if (position.x - radius <= windowRect.left || position.x + radius >= windowRect.right) velocity.x = -velocity.x;
    
    // 상단 경계 체크
    if (position.y - radius <= windowRect.top) velocity.y = -velocity.y;
    
    // 하단(화면밖)은 게임오버 처리 또는 리셋 로직 추가
}

void Ball::Render(HDC hdc)
{
    RECT circleRect;
    APIFuncs::SetRectCentered(position, Vector2(radius * 2, radius * 2), circleRect);
    APIFuncs::DrawCircle(hdc, circleRect);
    FillRect(hdc, &circleRect, ballBrush);
}