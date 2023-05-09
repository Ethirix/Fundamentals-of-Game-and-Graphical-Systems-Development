#pragma once
#include "Object.h"
class Text : public Object
{
public:
	explicit Text(const std::string& str, const ::Transform& transform = ::Transform(), const Vector3& color = Vector3(1, 1, 1));

	std::string String;
	Vector3 Color;
};

