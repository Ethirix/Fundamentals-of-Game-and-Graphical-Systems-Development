#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <optional>

#include "LinkedList.hpp"
#include "MeshData.h"
#include "TextCoords.h"
#include "Vector3.h"

class Mesh
{
public:
	Mesh() = default;

	MeshData<Vector3> IndexedVertices{};
	MeshData<Vector3> IndexedColors{};
	MeshData<TextCoords> TextureCoordinates{};
	MeshData<unsigned short> Indices{};

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

		file >> mesh->IndexedVertices.IndexLength;
		mesh->IndexedVertices.Index = new Vector3[mesh->IndexedVertices.IndexLength];
		for (unsigned i = 0; i < mesh->IndexedVertices.IndexLength; i++)
		{
			Vector3 v3;
			file >> line;
			v3.X = std::stof(line);
			file >> line;
			v3.Y = std::stof(line);
			file >> line;
			v3.Z = std::stof(line);
			mesh->IndexedVertices.Index[i] = v3;
		}

		file >> mesh->IndexedColors.IndexLength;
		mesh->IndexedColors.Index = new Vector3[mesh->IndexedColors.IndexLength];
		for (unsigned i = 0; i < mesh->IndexedColors.IndexLength; i++)
		{
			Vector3 v3;
			file >> line;
			v3.X = std::stof(line);
			file >> line;
			v3.Y = std::stof(line);
			file >> line;
			v3.Z = std::stof(line);
			mesh->IndexedColors.Index[i] = v3;
		}

		file >> mesh->TextureCoordinates.IndexLength;
		mesh->TextureCoordinates.Index = new TextCoords[mesh->TextureCoordinates.IndexLength];
		for (unsigned i = 0; i < mesh->TextureCoordinates.IndexLength; i++)
		{
			TextCoords coords{};
			file >> line;
			coords.U = std::stof(line);
			file >> line;
			coords.V = std::stof(line);

			mesh->TextureCoordinates.Index[i] = coords;
		}

		file >> mesh->Indices.IndexLength;
		mesh->Indices.Index = new unsigned short[mesh->Indices.IndexLength];
		for (unsigned i = 0; i < mesh->Indices.IndexLength; i++)
		{
			file >> line;
			mesh->Indices.Index[i] = std::stoi(line);
		}

		file.close();

		_loadedObjects.MakeNode(std::pair(path, mesh));

		return mesh;
	}

	static void CheckMeshExistsInGame()
	{
		ListNode<std::pair<std::string, std::shared_ptr<Mesh>>>* node = _loadedObjects.GetNode(0);

		while (node != nullptr)
		{
			const auto temp = node;
			node = node->Next;

			if (temp->Data.second.use_count() == 1)
			{
				_loadedObjects.DeleteAt(_loadedObjects.GetIndex(temp));
			}
		}
	}

private:
	inline static LinkedList<std::pair<std::string, std::shared_ptr<Mesh>>> _loadedObjects{};

	static std::optional<std::shared_ptr<Mesh>> HasModelAlreadyBeenLoaded(const std::string& key)
	{
		auto node = _loadedObjects.GetNode(0);

		while (node != nullptr)
		{
			if (node->Data.first == key)
			{
				return node->Data.second;
			}
			node = node->Next;
		}

		return {};
	}
};