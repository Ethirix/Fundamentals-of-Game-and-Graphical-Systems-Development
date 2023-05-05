#include "Matrix4x4.h"

Vector4 Matrix4x4::operator*(const Vector4& rhs)
{
	Vector4 v4;

	v4.X = (Matrix[0][0] * rhs.X) + 
		(Matrix[0][1] *rhs.Y) + 
		(Matrix[0][2] * rhs.Z) + 
		(Matrix[0][3] * rhs.W);

	v4.Y = (Matrix[1][0] * rhs.X) + 
		(Matrix[1][1] * rhs.Y) + 
		(Matrix[1][2] * rhs.Z) + 
		(Matrix[1][3] * rhs.W);

	v4.Z = (Matrix[2][0] * rhs.X) + 
		(Matrix[2][1] * rhs.Y) + 
		(Matrix[2][2] * rhs.Z) + 
		(Matrix[2][3] * rhs.W);

	v4.W = (Matrix[3][0] * rhs.X) + 
		(Matrix[3][1] * rhs.Y) + 
		(Matrix[3][2] * rhs.Z) + 
		(Matrix[3][3] * rhs.W);

	return v4;
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& rhs)
{
	Matrix4x4 m4x4;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m4x4.Matrix[i][j] = Matrix[i][j] + rhs.Matrix[i][j];
		}
	}

	return m4x4;
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& rhs)
{
	Matrix4x4 m4x4;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m4x4.Matrix[i][j] = Matrix[i][j] - rhs.Matrix[i][j];
		}
	}

	return m4x4;
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& rhs)
{
	Matrix4x4 m4x4;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m4x4.Matrix[i][j] = DotOperator(rhs, i, j);
		}
	}
	return m4x4;
}

float Matrix4x4::DotOperator(const Matrix4x4& rhs, const int row, const int col)
{
	float val = 0.0f;

	for (int i = 0; i < 4; i++)
	{
		val += Matrix[row][i] * rhs.Matrix[col][i];
	}

	return val;
}