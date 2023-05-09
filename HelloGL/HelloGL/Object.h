#pragma once
#include "Transform.h"
#include "Mesh.h"
#include <string>

#include "Material.h"
#include "Texture2D.h"

class Object
{
public:
	explicit Object(const std::string& meshPath = "", const std::string& texturePath = "", const Transform& transform = ::Transform(), Material material = ::Material());
	explicit Object(std::shared_ptr<Mesh> mesh, const Transform& transform = ::Transform());

	std::string Name;
	Transform Transform;
	Material Material;
	std::shared_ptr<Mesh> Mesh;
	std::shared_ptr<Texture2D> Texture;

	LinkedList<std::shared_ptr<Object>> Children = LinkedList<std::shared_ptr<Object>>();
};

