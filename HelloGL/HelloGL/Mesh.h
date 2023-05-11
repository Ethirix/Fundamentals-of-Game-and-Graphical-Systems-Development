#pragma once
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <optional>
#include <vector>

#include "LinkedList.hpp"
#include "MeshData.h"
#include "MeshLoadingData.h"
#include "TextCoords.h"
#include "Vector3.h"

#define MESH std::shared_ptr<Mesh>
#define OPTIONAL_MESH std::optional<MESH>

class Mesh
{
public:
	Mesh() = default;

	MeshData<Vector3> IndexedVertices{};
	MeshData<Vector3> IndexedNormals{};
 	MeshData<Vector3> IndexedColors{};
	MeshData<TextCoords> TextureCoordinates{};
	MeshData<unsigned short> VertexIndices{};
	MeshData<unsigned short> NormalIndices{};
	MeshData<unsigned short> TexCoordIndices{};

	static OPTIONAL_MESH LoadFromTXT(const std::string& path)
	{
		MESH mesh;
		if (const auto m  = HasModelAlreadyBeenLoaded(path))
		{
			mesh = m.value().Mesh;
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

		file >> mesh->VertexIndices.IndexLength;
		mesh->VertexIndices.Index = new unsigned short[mesh->VertexIndices.IndexLength];
		for (unsigned i = 0; i < mesh->VertexIndices.IndexLength; i++)
		{
			file >> line;
			mesh->VertexIndices.Index[i] = std::stoi(line);
		}

		file.close();

		_loadedObjects.MakeNode(std::pair(path, MeshLoadingData(mesh)));

		return mesh;
	}

	static std::optional<MeshLoadingData> LoadFromOBJ(const std::string& path)
	{
		MeshLoadingData meshData;
		if (const auto m  = HasModelAlreadyBeenLoaded(path))
		{
			meshData = m.value();
			return meshData;
		}
		meshData.Mesh = std::make_shared<Mesh>();

		std::ifstream file;
		std::string line;
		file.open(path);

		if (!file.good())
		{
			std::cout << "Mesh failed to load from file: " << path << std::endl;
			return {};
		}

		std::vector<Vector3> vertices, vertexNormals;
		std::vector<unsigned short> vertexIndices;
		std::vector<unsigned short> normalIndices;
		std::vector<unsigned short> texCoordIndices;
		std::vector<TextCoords> textCoords;

		while (std::getline(file, line))
		{
			std::istringstream sStream(line);
			std::string token;
			sStream >> token;

			if (token == "o")
			{
				sStream >> meshData.Name;
			}
			else if (token == "v")
			{
				Vector3 vector3{};
				sStream >> vector3.X;
				sStream >> vector3.Y;
				sStream >> vector3.Z;
				vertices.emplace_back(vector3);
			}
			else if (token == "vn")
			{
				Vector3 vector3{};
				sStream >> vector3.X;
				sStream >> vector3.Y;
				sStream >> vector3.Z;
				vertexNormals.emplace_back(vector3);
			}
			else if (token == "vt")
			{
				TextCoords tC{};
				sStream >> tC.U;
				sStream >> tC.V;
				textCoords.emplace_back(tC);
			}
			else if (token == "f")
			{
				std::vector<unsigned short> data;
				unsigned short nGonCheck = 0;

				while (true)
				{
					std::string setOfData;
					sStream >> setOfData;

					if (setOfData.empty())
						break;

					nGonCheck++;

					//CATCHES NONE TRIANGLE MESHES
					if (nGonCheck > 3)
						return {};

					std::replace(setOfData.begin(), setOfData.end(), '/', ' ');
					
					std::istringstream ss(setOfData);
					unsigned short temp;
					while (ss >> temp)
						data.emplace_back(temp - 1);

					vertexIndices.emplace_back(data[0]);
					texCoordIndices.emplace_back(data[1]);
					normalIndices.emplace_back(data[2]);
					data.clear();
				}
			}
		}

		meshData.Mesh->IndexedVertices.Index = new Vector3[vertices.size()];
		meshData.Mesh->IndexedVertices.IndexLength = vertices.size();
		for (unsigned i = 0; i < vertices.size(); i++)
		{
			meshData.Mesh->IndexedVertices.Index[i] = vertices[i];
		}

		meshData.Mesh->TextureCoordinates.Index = new TextCoords[textCoords.size()];
		meshData.Mesh->TextureCoordinates.IndexLength = textCoords.size();
		for (unsigned i = 0; i < textCoords.size(); i++)
		{
			meshData.Mesh->TextureCoordinates.Index[i] = textCoords[i];
		}

		meshData.Mesh->IndexedNormals.Index = new Vector3[vertexNormals.size()];
		meshData.Mesh->IndexedNormals.IndexLength = vertexNormals.size();
		for (unsigned i = 0; i < vertexNormals.size(); i++)
		{
			meshData.Mesh->IndexedNormals.Index[i] = vertexNormals[i];
		}

		meshData.Mesh->VertexIndices.Index = new unsigned short[vertexIndices.size()];
		meshData.Mesh->VertexIndices.IndexLength = vertexIndices.size();
		for (unsigned i = 0; i < vertexIndices.size(); i++)
		{
			meshData.Mesh->VertexIndices.Index[i] = vertexIndices[i];
		}

		meshData.Mesh->NormalIndices.Index = new unsigned short[normalIndices.size()];
		meshData.Mesh->NormalIndices.IndexLength = normalIndices.size();
		for (unsigned i = 0; i < normalIndices.size(); i++)
		{
			meshData.Mesh->NormalIndices.Index[i] = normalIndices[i];
		}

		meshData.Mesh->TexCoordIndices.Index = new unsigned short[texCoordIndices.size()];
		meshData.Mesh->TexCoordIndices.IndexLength = texCoordIndices.size();
		for (unsigned i = 0; i < texCoordIndices.size(); i++)
		{
			meshData.Mesh->TexCoordIndices.Index[i] = texCoordIndices[i];
		}

		_loadedObjects.MakeNode(std::pair(path, meshData));
		return meshData;
	}

	static void CheckMeshExistsInGame()
	{
		ListNode<std::pair<std::string, MeshLoadingData>>* node = _loadedObjects.GetNode(0);

		while (node != nullptr)
		{
			const auto temp = node;
			node = node->Next;

			if (temp->Data.second.Mesh.use_count() == 1)
			{
				_loadedObjects.DeleteAt(_loadedObjects.GetIndex(temp));
			}
		}
	}

private:
	inline static LinkedList<std::pair<std::string, MeshLoadingData>> _loadedObjects{};

	static std::optional<MeshLoadingData> HasModelAlreadyBeenLoaded(const std::string& key)
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