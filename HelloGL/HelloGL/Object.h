#pragma once
#include "Transform.h"
#include "Mesh.h"
#include <string>

class Object
{
public:
	explicit Object(std::shared_ptr<Mesh> mesh, Transform transform = ::Transform());

	std::string Name;
	Transform Transform;
	std::shared_ptr<Mesh> Mesh;

	LinkedList<std::shared_ptr<Object>> Children = LinkedList<std::shared_ptr<Object>>();
};

