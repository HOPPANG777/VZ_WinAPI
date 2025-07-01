#pragma once

#include "Utilities/APIFuncs.h"
#include "Systems/Time.h"
#include "Object.h"

class Rect : public Object
{
public:
	Rect() : Rect(Vector2(), Vector2(100, 100)) {}
	Rect(const Vector2& position, const Vector2& scale, COLORREF color = RGB(0, 0, 0), float maxSoeed = 200.0f)
		: position(position), scale(scale), maxSpeed(maxSpeed)
	{
		APIFuncs::SetRectCentered(position, scale, rect);
		SetColor(color);
	}

public:
	void Update(float deltaTime, const RECT& windowRect) override;
	void Render(HDC hdc) override;

public:
	void Move(const Vector2& position) { this->position += position * Time::Get()->GetDeltaTime(); }

public:
	Vector2 GetPosition() const { return position; }
	float GetSpeed() const { return speed; }

public:
	void SetPosition(const Vector2& position) { this->position = position; }
	void SetSpeed(const float speed) { this->speed = speed; }
	void SetMaxSpeed(const float maxSpeed) { this->maxSpeed = maxSpeed; }
	void SetColor(const COLORREF color) { this->brush = CreateSolidBrush(color); }

public:
	void AddKeyCount() { keyCount++; }
	void ResetKeyCount() { keyCount = 0; }
	bool CheckIntersect(const Rect& other) const;
	bool CheckIntersect(const Vector2& position) const;

private:
	RECT rect = { 0 };

	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));

	Vector2 position;
	Vector2 scale;

	float speed = 0.0f;
	float maxSpeed = 200.0f;

	int keyCount = 0;
};


