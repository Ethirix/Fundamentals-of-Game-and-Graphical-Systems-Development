#pragma once
#include "Object.h"
class SceneGraph
{
public:
	std::vector<std::shared_ptr<Object>> Objects = std::vector<std::shared_ptr<Object>>();

	Object& FindObjectWithName(std::string name);
	//std::vector<Object&> FindObjectsWithName(std::string name);


};

