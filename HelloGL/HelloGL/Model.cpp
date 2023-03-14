#include "Model.h"

Model::Model(const std::string& path)
{
	Load(path);
}


bool Model::Load(const std::string& path)
{
	std::ifstream file;
	std::string line;
	file.open(path);

	if(!file.good())
	{
		std::cout << "Model failed to load from file: " << path << std::endl;
		return false;
	}

	file >> IndexedVertices.second;
	IndexedVertices.first = new Vector3[IndexedVertices.second];
	for (unsigned i = 0; i < IndexedVertices.second; i++)
	{
		Vector3 v3;
		file >> line;
		v3.X = std::stof(line);
		file >> line;
		v3.Y = std::stof(line);
		file >> line;
		v3.Z = std::stof(line);
		IndexedVertices.first[i] = v3;
	}

	file >> IndexedColors.second;
	IndexedColors.first = new Vector3[IndexedColors.second];
	for (unsigned i = 0; i < IndexedColors.second; i++)
	{
		Vector3 v3;
		file >> line;
		v3.X = std::stof(line);
		file >> line;
		v3.Y = std::stof(line);
		file >> line;
		v3.Z = std::stof(line);
		IndexedColors.first[i] = v3;
	}

	file >> Indices.second;
	Indices.first = new unsigned short[Indices.second];
	for (unsigned i = 0; i < Indices.second; i++)
	{
		file >> line;
		Indices.first[i] = std::stoi(line);
	}

	file.close();

	return true;
}
