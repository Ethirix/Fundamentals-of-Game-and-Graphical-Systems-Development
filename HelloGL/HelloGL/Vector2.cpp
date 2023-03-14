#include "Vector2.h"

Vector2::Vector2(int x, int y)
{
	X = static_cast<float>(x);
	Y = static_cast<float>(y);
}


Vector2::Vector2(float x, float y)
{
	X = x;
	Y = y;
}

Vector2 Vector2::operator+(const Vector2& rhs)
{
	Vector2 v2;
	v2.X = X + rhs.X;
	v2.Y = Y + rhs.Y;

	return v2;
}

Vector2 Vector2::operator-(const Vector2& rhs)
{
	Vector2 v2;
	v2.X = X - rhs.X;
	v2.Y = Y - rhs.Y;

	return v2;
}

bool Vector2::operator==(const Vector2& vector2) const
{
	return (X >= vector2.X - 0.0005f && X <= vector2.X + 0.0005f) && (Y >= vector2.Y - 0.0005f && Y <= vector2.Y + 0.0005f);
}
