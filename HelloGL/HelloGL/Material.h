#pragma once
#include "Vector4.h"

class Material
{
public:
	Material();
	Material(const Vector4& ambient, const Vector4& diffuse, const Vector4& specular, float shininess);

	Vector4 Ambient;
	Vector4 Diffuse;
	Vector4 Specular;
	float Shininess;
};
