#include "Material.h"

Material::Material(const Vector4& ambient, const Vector4& diffuse, const Vector4& specular, float shininess)
{
	Ambient = ambient;
	Diffuse = diffuse;
	Specular = specular;
	Shininess = shininess;
}
