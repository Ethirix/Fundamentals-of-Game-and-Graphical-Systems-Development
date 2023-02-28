#pragma once

class Vector3
{
public:
	explicit Vector3(float x = 0, float y = 0, float z = 0);

	float X;
	float Y;
	float Z;

	Vector3 operator+ (const Vector3& rhs);
	Vector3 operator- (const Vector3& rhs);
};