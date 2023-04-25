#pragma once
#include <optional>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>

#include "LinkedList.hpp"

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

class Texture2D
{
public:
	Texture2D() = default;
	Texture2D(unsigned id, unsigned width, unsigned height);
	Texture2D(const Texture2D &texture2D);

	~Texture2D();

	static std::optional<std::shared_ptr<Texture2D>> Load(const std::string& path)
	{
		if (auto file = LoadRAW(path); file.has_value())
		{
			return file.value();
		}
		return{};
	}

	[[nodiscard]] unsigned GetID() const;
	[[nodiscard]] unsigned GetWidth() const;
	[[nodiscard]] unsigned GetHeight() const;

private:
	unsigned _id = 0;
	unsigned _width = 0;
	unsigned _height = 0;

	static inline LinkedList<std::pair<std::string, std::shared_ptr<Texture2D>>> _loadedTextures{};

	static std::optional<std::shared_ptr<Texture2D>> IsTextureLoaded(const std::string& key)
	{
		auto node = _loadedTextures.GetNode(0);

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

	static std::optional<std::shared_ptr<Texture2D>> LoadRAW(const std::string& path)
	{
		if (auto texture2d = IsTextureLoaded(path); texture2d.has_value())
		{
			return texture2d.value();
		}

		std::ifstream file;
		
		file.open(path, std::ios::binary);

		if (!file.good())
		{
			std::cout << "Failed to open file at path: " << path << std::endl;
			return {};
		}

		const auto size = static_cast<unsigned>(std::filesystem::file_size(path));
		float imageSizeF = sqrt((size * 8) / 24);

		if (floorf(imageSizeF) != imageSizeF)
		{
			std::cout << "Image is not a square - path: " << path << std::endl;
			return {};
		}

		auto imageSize = static_cast<unsigned>(imageSizeF);

		if ((imageSize & imageSize - 1) != 0)
		{
			std::cout << "File size is not Power of 2 - path: " << path << std::endl;
			return {};
		}

		char* textureData = new char[size];
		file.read(textureData, size);
		file.close();

		unsigned id;
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, imageSize, imageSize, GL_RGB, GL_UNSIGNED_BYTE, textureData);

		auto texture2D = std::make_shared<Texture2D>(id, imageSize, imageSize);
		_loadedTextures.MakeNode(std::pair(path, texture2D));

		delete[] textureData;
		return texture2D;
	}
};

