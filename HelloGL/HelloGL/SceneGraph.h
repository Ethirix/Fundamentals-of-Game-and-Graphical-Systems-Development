#pragma once
#include "Object.h"
#include "LinkedList.hpp"
class SceneGraph
{
public:
	LinkedList<std::shared_ptr<Object>> Objects;
};