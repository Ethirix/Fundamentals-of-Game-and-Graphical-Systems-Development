#include "TextureManager.h"

void TextureManager::InitializeTextureManager()
{
	TextureMap["pacman"] = "Textures/Pacman.tga";
	TextureMap["munchie"] = "Textures/Munchie.tga";
	TextureMap["munchieInverted"] = "Textures/MunchieInverted.tga";
	TextureMap["transparency"] = "Textures/Transparency.png";
}

std::map<std::string, std::string> TextureManager::TextureMap;
