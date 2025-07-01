#pragma once

#include "Utilities/Vector.h"
#include "Utilities/APIFuncs.h"
#include "GameObject.h"

class Ball : public GameObject
{
public:
    Ball(const Vector2& pos, const Vector2& vel, float radius, COLORREF color = RGB(0, 0, 0))
        : position(pos), velocity(vel), radius(radius)
    {
        ballBrush = CreateSolidBrush(color);
    }
    ~Ball()
    {
        DeleteObject(ballBrush);
    }

public:
    void Update(float deltaTime, const RECT& windowRect) override;
    void Render(HDC hdc) override;

public:
    const Vector2& GetPosition() const { return position; }
    float GetRadius() const { return radius; }

public:
    bool CheckCollision(const RECT& r) const
    {
        return
            (
                position.x + radius >= r.left &&
                position.x - radius <= r.right &&
                position.y + radius >= r.top &&
                position.y - radius <= r.bottom
            );
    }

public:
    void ReflectVertical() { velocity.y = -velocity.y; }
    void ReflectHorizontal() { velocity.x = -velocity.x; }

private:
    Vector2 position;
    Vector2 velocity;
    float radius;
    
    HBRUSH ballBrush = nullptr;
};
