#pragma once
#include <string>
#include <map>
#include "Block.h"

class MapLoader
{
public:
	/**
	 * \brief Path to where Maps are located.
	 */
	const std::string Path = "Maps/";

	/**
	 * \brief Loads the Map into the GameObjectManager.
	 */
	void LoadMap();

private:
	std::map<char, GameObject*> InitializeMap();
};

