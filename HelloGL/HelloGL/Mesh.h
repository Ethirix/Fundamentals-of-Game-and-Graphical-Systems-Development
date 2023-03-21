#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <optional>
#include <vector>

#include "Vector3.h"

class Mesh
{
public:
	Mesh() = default;
	Mesh(const std::string& path);

	std::pair<Vector3*, unsigned> IndexedVertices{};
	std::pair<Vector3*, unsigned> IndexedColors{};
	std::pair<unsigned short*, unsigned> Indices{};

	static std::optional<std::shared_ptr<Mesh>> LoadFromTXT(const std::string& path)
	{
		std::shared_ptr<Mesh> mesh;
		if (const auto m  = HasModelAlreadyBeenLoaded(path))
		{
			mesh = m.value();
			return mesh;
		}
		mesh = std::make_shared<Mesh>();

		std::ifstream file;
		std::string line;
		file.open(path);

		if (!file.good())
		{
			std::cout << "Mesh failed to load from file: " << path << std::endl;
			return {};
		}

		file >> mesh->IndexedVertices.second;
		mesh->IndexedVertices.first = new Vector3[mesh->IndexedVertices.second];
		for (unsigned i = 0; i < mesh->IndexedVertices.second; i++)
		{
			Vector3 v3;
			file >> line;
			v3.X = std::stof(line);
			file >> line;
			v3.Y = std::stof(line);
			file >> line;
			v3.Z = std::stof(line);
			mesh->IndexedVertices.first[i] = v3;
		}

		file >> mesh->IndexedColors.second;
		mesh->IndexedColors.first = new Vector3[mesh->IndexedColors.second];
		for (unsigned i = 0; i < mesh->IndexedColors.second; i++)
		{
			Vector3 v3;
			file >> line;
			v3.X = std::stof(line);
			file >> line;
			v3.Y = std::stof(line);
			file >> line;
			v3.Z = std::stof(line);
			mesh->IndexedColors.first[i] = v3;
		}

		file >> mesh->Indices.second;
		mesh->Indices.first = new unsigned short[mesh->Indices.second];
		for (unsigned i = 0; i < mesh->Indices.second; i++)
		{
			file >> line;
			mesh->Indices.first[i] = std::stoi(line);
		}

		file.close();

		_loadedObjects.emplace_back(path, mesh);

		return mesh;
	}

	static void CheckMeshExistsInGame()
	{
		for (int i = 0; i < _loadedObjects.size(); i++)
		{
			if (_loadedObjects[i].second.use_count() == 1)
			{
				_loadedObjects.erase(_loadedObjects.begin() + i);
			}
		}
	}

private:
	inline static std::vector<std::pair<std::string, std::shared_ptr<Mesh>>> _loadedObjects{};

	static std::optional<std::shared_ptr<Mesh>> HasModelAlreadyBeenLoaded(const std::string& key)
	{
		for (auto& [meshKey, mesh] : _loadedObjects)
		{
			if (meshKey == key)
			{
				return mesh;
			}
		}

		return {};
	}
};


