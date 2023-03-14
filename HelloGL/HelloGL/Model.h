#pragma once
#include <string>
#include <iostream>
#include <fstream>

#include "Vector3.h"

class Model
{
public:
	Model() = default;
	explicit Model(const std::string& path);

	std::pair<Vector3*, unsigned> IndexedVertices;
	std::pair<Vector3*, unsigned> IndexedColors;
	std::pair<unsigned short*, unsigned> Indices;

private:
	bool Load(const std::string& path);
};


