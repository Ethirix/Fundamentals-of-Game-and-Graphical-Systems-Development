#pragma once
#include <memory>
#include <string>

class Mesh;

struct MeshLoadingData
{
	MeshLoadingData() = default;
	MeshLoadingData(const std::shared_ptr<Mesh>& mesh)
	{
		Mesh = mesh;
	}

	std::string Name;
	std::shared_ptr<Mesh> Mesh;
};
