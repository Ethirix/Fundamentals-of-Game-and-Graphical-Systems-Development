#pragma once
#include "Vector3.h"

class Transform
{
public:
	explicit Transform(Vector3 position = Vector3(), Vector3 rotation = Vector3());

	Vector3 Position;
	Vector3 Rotation;
};