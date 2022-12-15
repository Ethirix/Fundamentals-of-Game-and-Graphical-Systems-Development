#pragma once

#include <map>
#include <string>

class TextureManager
{
public:
	/**
	 * \brief Initializes the TextureManager.
	 */
	static void InitializeTextureManager();
	/**
	 * \brief Converts a string to all lower case characters.
	 * \param str String to be put in lower case.
	 * \return The string in lower case.
	 */
	static std::string ToLower(std::string str);

	/**
	 * \brief The map that puts TextureKey to a Texture location on disk.
	 */
	static std::map<std::string, std::string> TextureMap;

	
};
