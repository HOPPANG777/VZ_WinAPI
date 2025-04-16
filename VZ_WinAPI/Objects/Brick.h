#pragma once

#include "Utilities/Vector.h"
#include "Utilities/APIFuncs.h"

class Brick
{
public:
    Brick(const Vector2& pos, const Vector2& size, COLORREF color = RGB(255, 0, 0))
        : position(pos), size(size), active(true)
    {
        brickBrush = CreateSolidBrush(color);
        APIFuncs::SetRectCentered(position, size, rect);
    }
    ~Brick()
    {
        DeleteObject(brickBrush);
    }

public:
    void Render(HDC hdc);

public:
    bool IsActive() const { return active; }
    void Destroy() { active = false; }

public:
    const RECT& GetRect() const { return rect; }

private:
    Vector2 position;
    Vector2 size;
    
    RECT rect = { 0 };
    
    bool active;
    HBRUSH brickBrush = nullptr;

};
