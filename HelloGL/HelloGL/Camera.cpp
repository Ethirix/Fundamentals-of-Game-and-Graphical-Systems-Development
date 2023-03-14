#include "Camera.h"

Camera::Camera()
{
	Eye = Vector3(0, 0, 1.0f);
	Center = Vector3(0, 0, 0);
	Up = Vector3(0, 1.0f, 0);
}


Camera::Camera(Vector3 eye, Vector3 center, Vector3 up)
{
	Eye = eye;
	Center = center;
	Up = up;
}
