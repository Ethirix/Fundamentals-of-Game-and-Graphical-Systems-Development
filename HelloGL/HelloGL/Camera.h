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

	Vector3 Position;

	float Pitch = 0;
	float Yaw = 0;
	float Roll = 0;

	float FieldOfView = 90.0f;
	float NearPlane = 0.1f;
	float FarPlane = 1000.0f;
};