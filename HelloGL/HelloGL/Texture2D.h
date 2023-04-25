#pragma once
#include <optional>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>

#include "LinkedList.hpp"

#include <Windows.h>
#include <gl/GL.h>

class Texture2D
{
public:
	~Texture2D();

	static std::optional<std::shared_ptr<Texture2D>> Load(std::string path)
	{
		auto file = LoadRAW(path);
		if (file.has_value())
		{
			return file.value();
		}
		return{};
	}

	[[nodiscard]] unsigned GetID() const;
	[[nodiscard]] unsigned GetWidth() const;
	[[nodiscard]] unsigned GetHeight() const;

private:
	Texture2D(unsigned id, unsigned width, unsigned height);

	unsigned _id;
	unsigned _width;
	unsigned _height;

	static inline LinkedList<std::pair<std::string, std::shared_ptr<Texture2D>>> _loadedTextures{};

	static std::optional<std::shared_ptr<Texture2D>> IsTextureLoaded(std::string key)
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
		std::ifstream file;
		
		file.open(path, std::ios::binary);

		if (!file.good())
		{
			std::cout << "Failed to open file at path: " << path << std::endl;
			return {};
		}

		const auto size = static_cast<unsigned>(std::filesystem::file_size(path));
		const auto imageSize = static_cast<unsigned>(sqrt((size * 8) / 24));

		const auto textureData = new char[size];
		file.read(textureData, size);

		if ((size & size - 1) != 0)
		{
			std::cout << "File size is not Power of 2 - path: " << path << std::endl;
			return {};
		}
		unsigned id;
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageSize, imageSize, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, textureData);
		delete[] textureData;
		file.close();

		auto texture2D = std::make_shared<Texture2D>(Texture2D(id, imageSize, imageSize));
		return texture2D;
	}
};

