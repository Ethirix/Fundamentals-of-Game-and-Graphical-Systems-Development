#include "Model.h"

#include <utility>

Model::Model(std::vector<Vector3> indexedVertices, std::vector<Vector3> indexedColors, std::vector<unsigned short> indices)
{
	IndexedVertices = std::move(indexedVertices);
	IndexedColors = std::move(indexedColors);
	Indices = std::move(indices);
}
