#pragma once

class Vector4
{
public:
	explicit Vector4(float x = 0, float y = 0, float z = 0, float w = 0);

	float X;
	float Y;
	float Z;
	float W;

	Vector4 operator+(const Vector4& rhs);
	Vector4 operator-(const Vector4& rhs);
};

