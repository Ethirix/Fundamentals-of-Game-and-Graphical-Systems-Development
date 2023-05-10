#pragma once
#include <cmath>

class Vector3
{
public:
	explicit Vector3(float x = 0, float y = 0, float z = 0);

	float X;
	float Y;
	float Z;

	Vector3 operator+ (const Vector3& rhs);
	Vector3 operator- (const Vector3& rhs);
	Vector3 operator* (float rhs);

	Vector3 operator+= (const Vector3& rhs);
	Vector3 operator-= (const Vector3& rhs);

	Vector3 Normalize();
	float Magnitude();

	static float Magnitude(const Vector3 a)
	{
		return abs(sqrt(a.X * a.X + a.Y * a.Y + a.Z * a.Z));
	}

	//static Vector3 Cross(Vector3 a, Vector3 b)
	//{
	//	Vector3 c;
	//	float lenA = abs(sqrt(a.X * a.X + a.Y * a.Y + a.Z + a.Z));
	//	float lenB = abs(sqrt(b.X * b.X + b.Y * b.Y + b.Z + b.Z));
	//	float angle = acos((a.X * b.X + a.Y * b.Y) / (lenA * lenB));
	//	float length = lenA * lenB * sin(angle);
	//}

	static float AngleBetween(Vector3 a, Vector3 b)
	{
		const float dot = DotProduct(a, b);
		const float magA = a.Magnitude();
		const float magB = b.Magnitude();

		if (magA * magB == 0)
			return 0;

		return acos(dot / (magA * magB));
	}

	static float DotProduct(const Vector3 a, const Vector3 b)
	{
		return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
	}
};
