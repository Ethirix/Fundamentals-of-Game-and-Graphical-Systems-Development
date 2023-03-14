#include "Vector3.h"

Vector3::Vector3(float x, float y, float z)
{
	X = x;
	Y = y;
	Z = z;
}

Vector3 Vector3::operator+(const Vector3& rhs)
{
	Vector3 v3;

	v3.X = X + rhs.X;
	v3.Y = Y + rhs.Y;
	v3.Z = Z + rhs.Z;

	return v3;
}

Vector3 Vector3::operator-(const Vector3& rhs)
{
	Vector3 v3;

	v3.X = X - rhs.X;
	v3.Y = Y - rhs.Y;
	v3.Z = Z - rhs.Z;

	return v3;
}
