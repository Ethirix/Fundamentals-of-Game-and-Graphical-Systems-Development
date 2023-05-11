#pragma once
#include "Vector4.h"

class Material
{
public:
	explicit Material(const Vector4& ambient = Vector4(1.0f, 1.0f, 1.0f, 1.0f), 
	                  const Vector4& diffuse = Vector4(1.0f, 1.0f, 1.0f, 1.0f), 
	                  const Vector4& specular = Vector4(0.5f, 0.5f, 0.5f, 1.0f), 
	                  float shininess = 50.0f);

	Vector4 Ambient;
	Vector4 Diffuse;
	Vector4 Specular;
	float Shininess;
};
