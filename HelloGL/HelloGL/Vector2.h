#pragma once

class Vector2
{
public:
	explicit Vector2(int x = 0, int y = 0);
	explicit Vector2(float x = 0, float y = 0);

	float X;
	float Y;

	Vector2 operator+ (const Vector2& rhs);
	Vector2 operator- (const Vector2& rhs);
	bool operator==(const Vector2& vector2) const;
};

