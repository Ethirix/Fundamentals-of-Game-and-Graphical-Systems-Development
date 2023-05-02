#include "Object.h"

#include <utility>

#include "Texture2D.h"

Object::Object(std::shared_ptr<::Mesh> mesh, const ::Transform& transform)
{
	Mesh = std::move(mesh);
	Texture = std::make_shared<Texture2D>();
	Transform = transform;
}

Object::Object(const std::string& meshPath, const std::string& texturePath, const ::Transform& transform)
{
	if (const auto possibleMesh = Mesh::LoadFromTXT(meshPath); possibleMesh.has_value())
	{
		Mesh = possibleMesh.value();
	}

	if (const auto possibleText = Texture2D::Load(texturePath); possibleText.has_value())
	{
		Texture = possibleText.value();
	}

	Transform = transform;
}
