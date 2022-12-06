#include "TextureManager.h"

#include <iostream>
#include <filesystem>

void TextureManager::InitializeTextureManager()
{
	std::string path = "Textures/";
	for (auto& file : std::filesystem::recursive_directory_iterator(path))
	{
		std::string fileName = file.path().filename().string();
		std::string culledFileName;

		if (fileName.find(".txt") != std::string::npos)
			continue;

		for (int i = 0; i < static_cast<int>(fileName.length()); i++)
		{
			if (fileName[i] == '.')
			{
				culledFileName = fileName.substr(0, i);
			}
		}

		TextureMap[ToLower(culledFileName)] = file.path().string(); //+ fileName;
	}
}

std::string TextureManager::ToLower(std::string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		str[i] = tolower(str[i]);
	}

	return str;
}

std::map<std::string, std::string> TextureManager::TextureMap;
