#include "Text.h"

Text::Text(const std::string& str, const ::Transform& transform, const Vector3& color)
{
	String = str;
	Transform = transform;
	Mesh = nullptr;
	Texture = nullptr;
	Color = color;
}
