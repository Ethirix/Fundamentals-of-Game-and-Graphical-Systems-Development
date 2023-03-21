#include "Object.h"

#include <utility>

Object::Object(std::shared_ptr<::Mesh> mesh, ::Transform transform)
{
	Mesh = std::move(mesh);
	Transform = transform;
}