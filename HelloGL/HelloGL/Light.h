#pragma once
#include "Lighting.h"
#include "Object.h"

class Light
{
public:
	explicit Light();
	explicit Light(const Vector3& position, const Lighting& lightData);

	std::string Name;
	Vector3 Position;
	Lighting Lighting;
};

