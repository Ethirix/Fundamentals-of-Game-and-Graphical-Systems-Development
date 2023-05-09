#include "Material.h"

Material::Material()
{
	Ambient = Vector4();
	Diffuse = Vector4();
	Specular = Vector4();
	Shininess = 0.0f;
}


Material::Material(const Vector4& ambient, const Vector4& diffuse, const Vector4& specular, float shininess)
{
	Ambient = ambient;
	Diffuse = diffuse;
	Specular = specular;
	Shininess = shininess;
}
