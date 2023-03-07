#pragma once
#include "Transform.h"
#include "Model.h"
#include <string>

class Object
{
public:
	explicit Object(Model::Model model, Transform transform = ::Transform());

	std::string Name;
	Transform Transform;
	Model::Model Model;

	std::vector<Object> Children = std::vector<Object>();
};

