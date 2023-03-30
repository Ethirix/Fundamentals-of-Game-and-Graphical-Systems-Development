#pragma once
#include "Object.h"
#include "LinkedList.hpp"
class SceneGraph
{
public:
	std::vector<std::shared_ptr<Object>> Objects = std::vector<std::shared_ptr<Object>>();

	LinkedList<std::shared_ptr<Object>> _Objects;
};