#include "Light.h"

Light::Light()
{
	Name = "LIGHT0";
	Position = Vector3();
	Lighting = ::Lighting();
}

Light::Light(const Vector3& position, const ::Lighting& lightData)
{
	Name = "LIGHT0";
	Position = position;

	Lighting = lightData;
}
