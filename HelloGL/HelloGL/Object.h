#pragma once
#include "Transform.h"
#include "Model.h"
#include <string>
#include <vector>

class Object
{
public:
	explicit Object(Model model, Transform transform = ::Transform());

	std::string Name;
	Transform Transform;
	Model Model;

	std::vector<Object> Children = std::vector<Object>();
};

