#include "Object.h"

#include <utility>

Object::Object(::Model model, ::Transform transform)
{
	Model = std::move(model);
	Transform = transform;
}