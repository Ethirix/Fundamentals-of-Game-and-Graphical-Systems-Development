#include "Vector2.h"

Vector2::Vector2(int x, int y)
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
	return X == vector2.X && Y == vector2.Y;
}
