#pragma once
#include <string>
#include <map>
#include "Block.h"

class MapLoader
{
public:
	const std::string Path = "Maps/";
	void LoadMap();

private:
	std::map<char, GameObject*> InitializeMap();
};

