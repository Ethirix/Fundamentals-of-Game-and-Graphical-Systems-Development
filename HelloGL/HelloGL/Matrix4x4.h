#pragma once
#include "Vector4.h"

class Matrix4x4
{
public:
	float Matrix[4][4]{};

	Vector4 operator*(const Vector4& rhs);

	Matrix4x4 operator+(const Matrix4x4& rhs);
	Matrix4x4 operator-(const Matrix4x4& rhs);
	Matrix4x4 operator*(const Matrix4x4& rhs);

private:
	float DotOperator(const Matrix4x4& rhs, int row, int col);
};

