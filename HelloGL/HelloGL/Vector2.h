#pragma once

class Vector2
{
public:
	explicit Vector2(int x = 0, int y = 0);

	int X;
	int Y;

	Vector2 operator+ (const Vector2& rhs);
	Vector2 operator- (const Vector2& rhs);
	bool operator==(const Vector2& vector2) const;
};