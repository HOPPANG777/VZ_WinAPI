#pragma once

class Vector2
{
public:
	float x;
	float y;

public:
	Vector2() : Vector2(0.0f, 0.0f) {}
	Vector2(float x, float y) : x(x), y(y) {}
	Vector2(int x, int y) : Vector2(float(x), float(y)) {}
	Vector2(int x, float y) : Vector2(float(x), y) {}
	Vector2(float x, int y) : Vector2(x, float(y)) {}
	Vector2(const Vector2& other) { *this = other; }

public:
	Vector2& operator=(const Vector2& other)
	{
		x = other.x;
		y = other.y;
		return *this;
	}

public:
	Vector2 operator+(const Vector2& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}
	Vector2 operator-(const Vector2& other) const
	{
		return Vector2(x - other.x, y - other.y);
	}

public:
	Vector2 operator*(const float scalar) const
	{
		return Vector2(x * scalar, y * scalar);
	}
	Vector2 operator/(const float scalar) const
	{
		return Vector2(x / scalar, y / scalar);
	}

public:
	Vector2& operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	Vector2& operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

public:
	Vector2& operator*=(const float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}
	Vector2& operator/=(const float scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}

public:
	POINT ToPoint() const
	{
		return POINT{ LONG(x), LONG(y) };
	}

};