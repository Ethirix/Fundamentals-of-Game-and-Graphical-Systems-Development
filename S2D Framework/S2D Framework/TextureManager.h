#pragma once

#include <map>
#include <string>

class TextureManager
{
public:
	static void InitializeTextureManager();

	static std::map<std::string, std::string> TextureMap;
};
