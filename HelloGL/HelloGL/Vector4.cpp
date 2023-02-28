#include "Vector4.h"

Vector4::Vector4(float x, float y, float z, float w)
{
	X = x;
	Y = y;
	Z = z;
	W = w;
}

Vector4 Vector4::operator+(const Vector4& rhs)
{
	Vector4 v4 = Vector4();

	v4.X = X + rhs.X;
	v4.Y = Y + rhs.Y;
	v4.Z = Z + rhs.Z;
	v4.W = W + rhs.W;

	return v4;
}

Vector4 Vector4::operator-(const Vector4& rhs)
{
	Vector4 v4 = Vector4();

	v4.X = X - rhs.X;
	v4.Y = Y - rhs.Y;
	v4.Z = Z - rhs.Z;
	v4.W = W - rhs.W;

	return v4;
}