#pragma once
#include <vector>

#include "Vector3.h"

class Model
{
public:
	Model() = default;
	Model(std::vector<Vector3> indexedVertices, 
		std::vector<Vector3> indexedColors, 
		std::vector<unsigned short> indices);

	std::vector<Vector3> IndexedVertices{};
	std::vector<Vector3> IndexedColors{};
	std::vector<unsigned short> Indices{};

	std::pair<Vector3*, unsigned int> GetArrayOfIndexedVertices()
	{
		return {IndexedVertices.data(), IndexedVertices.size() };
	}

	std::pair<Vector3*, unsigned int> GetArrayOfIndexedColors()
	{
		return {IndexedColors.data(), IndexedColors.size() };
	}

	std::pair<unsigned short*, unsigned int> GetArrayOfIndices()
	{
		return { Indices.data(), Indices.size() };
	}
};


