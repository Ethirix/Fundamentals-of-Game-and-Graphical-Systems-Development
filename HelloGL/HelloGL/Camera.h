#pragma once
#include "Vector3.h"

class Camera
{
public:
	Camera();
	Camera(Vector3 eye, Vector3 center, Vector3 up);

	Vector3 Eye;
	Vector3 Center;
	Vector3 Up;
};

