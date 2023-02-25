#include "Object.h"

#include <utility>

Object::Object(Model::Model model, ::Transform transform)
{
	Model = std::move(model);
	Transform = transform;
}