#include "Vector3.h"

#include <cmath>

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

Vector3 Vector3::operator*(const float rhs)
{
	Vector3 v3;

	v3.X = X * rhs;
	v3.Y = Y * rhs;
	v3.Z = Z * rhs;

	return v3;
}

float Vector3::Magnitude()
{
	return abs(sqrt(X * X + Y * Y + Z * Z));
}


Vector3 Vector3::Normalize()
{
	float length = abs(sqrt(X * X + Y * Y + Z * Z));
	return Vector3(X / length, Y / length, Z / length);
}