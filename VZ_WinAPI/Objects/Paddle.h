#pragma once

#include "Utilities/Vector.h"
#include "Utilities/APIFuncs.h"
#include "Systems/Input.h"
#include "Object.h"

class Paddle : public Object
{
public:
    Paddle(const Vector2& pos, const Vector2& size, COLORREF color = RGB(0, 255, 0))
        : position(pos), size(size)
    {
        rectBrush = CreateSolidBrush(color);
        APIFuncs::SetRectCentered(position, size, rect);
    }
    ~Paddle()
    {
        DeleteObject(rectBrush);
    }

public:
    void Update(float deltaTime, const RECT& windowRect) override;
    void Render(HDC hdc) override;

public:
    const RECT& GetRect() const { return rect; }

private:
    Vector2 position;
    Vector2 size;

    RECT rect = { 0 };
    HBRUSH rectBrush = nullptr;
    
    float speed = 500.0f; // 이동 속도
};
