#pragma once

#include "S2D/S2D.h"
#include <string>

class GameObject
{
public:
	/**
	 * \brief Base Constructor for GameObject.
	 */
	GameObject() = default;
	/**
	 * \brief Creates a Copy of a GameObject.
	 * \param gO GameObject to copy.
	 */
	GameObject(const GameObject& gO);
	virtual ~GameObject() = default;
	/**
	 * \brief Function that runs during the game Update().
	 * \param elapsedTime Time between frames.
	 */
	virtual void Update(int elapsedTime);
	/**
	 * \brief Loads the textures for the GameObject before the main loop runs.
	 */
	virtual void Load();

	/**
	 * \brief Position of the GameObject.
	 */
	S2D::Vector2* Position = new S2D::Vector2(0.0f, 0.0f);
	/**
	 * \brief Texture of the GameObject.
	 */
	S2D::Texture2D* Texture = new S2D::Texture2D();
	/**
	 * \brief SourceRect of the GameObject.
	 */
	S2D::Rect* SourceRect = new S2D::Rect();

	/**
	 * \brief Gets the RenderDepth of the GameObject.
	 * \return The RenderDepth.
	 */
	int GetRenderDepth();

	/**
	 * \brief Gets the TextureKey that defines the GameObject's Textures during Load().
	 * \return The TextureKey.
	 */
	std::string GetTextureKey();

protected:
	std::string _textureKey;
	int _renderDepth = 5;
};