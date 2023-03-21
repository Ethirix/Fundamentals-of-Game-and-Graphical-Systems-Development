#pragma once
#include "Transform.h"
#include "Mesh.h"
#include <string>
#include <vector>

class Object
{
public:
	explicit Object(std::shared_ptr<Mesh> mesh, Transform transform = ::Transform());

	std::string Name;
	Transform Transform;
	std::shared_ptr<Mesh> Mesh;

	std::vector<std::shared_ptr<Object>> Children = std::vector<std::shared_ptr<Object>>();
};

