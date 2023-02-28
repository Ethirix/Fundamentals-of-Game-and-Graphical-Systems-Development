#pragma once
#include "Vector3.h"
#include "Matrix4x4.h"

class Transform
{
public:
	explicit Transform(Vector4 position = Vector4(), Vector4 rotation = Vector4());

	Vector4 Position;
	Vector4 Rotation;

	Matrix4x4 TranslationMatrix;
	Matrix4x4 RotationMatrix;
	Matrix4x4 ScaleMatrix;

	Vector4 GlobalPosition = Vector4();
	Vector4 GlobalRotation = Vector4();
};