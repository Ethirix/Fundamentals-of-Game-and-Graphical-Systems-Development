#pragma once
#include "Vector4.h"

class Lighting
{
public:
	Lighting()
	{
		Ambient = Vector4();
		Diffuse = Vector4();
		Specular = Vector4();
	}

	Lighting(const Vector4& ambient, const Vector4& diffuse, const Vector4& specular)
	{
		Ambient = ambient;
		Diffuse = diffuse;
		Specular = specular;
	}

	Vector4 Ambient;
	Vector4 Diffuse;
	Vector4 Specular;
};

