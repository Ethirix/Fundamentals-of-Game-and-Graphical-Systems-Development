#pragma once
#include "Object.h"
class SceneGraph
{
public:
	std::vector<Object> Objects = std::vector<Object>();

	Object& FindObjectWithName(std::string name);
	//std::vector<Object&> FindObjectsWithName(std::string name);


};

