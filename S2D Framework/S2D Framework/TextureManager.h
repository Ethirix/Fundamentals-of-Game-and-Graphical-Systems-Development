#pragma once

#include <map>
#include <string>

class TextureManager
{
public:
	static void InitializeTextureManager();
	static std::string ToLower(std::string str);

	static std::map<std::string, std::string> TextureMap;

	
};
