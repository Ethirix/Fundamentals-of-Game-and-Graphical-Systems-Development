#pragma once
#include <vector>

#include "GameObject.h"
#include "Player.h"
#include "RenderQueue.h"

typedef GameObject* GameObject_P;
typedef Collidable* Collidable_P;

class GameObjectManager
{
public:
	/**
	 * \brief Base Constructor for the GameObjectManager.
	 */
	GameObjectManager();
	~GameObjectManager();

	/**
	 * \brief Adds a GameObject to the Game.
	 * \param gO The GameObject to add.
	 */
	void AddGameObject(GameObject_P gO);

	/**
	 * \brief Removes the GameObject from the Game.
	 * \param gO The GameObject to remove.
	 */
	void DestroyGameObject(GameObject_P gO);
	/**
	 * \brief MUST RUN AT END OF FRAME: Removes the GameObjects from memory that have been removed that Frame.
	 */
	void FlushGameObjects();
	/**
	 * \brief Checks if the GameObject has collided with any other GameObject in the scene.
	 * \param gO The GameObject to check for Collisions with.
	 * \return The GameObject that has been collided with - nullptr if none.
	 */
	GameObject_P HasGameObjectCollided(GameObject_P gO);

	/**
	 * \brief Loads a GameObject's Texture if created after LoadGameObjectTextures().
	 * \param gO The GameObject to load the Texture of.
	 */
	void LoadGameObjectTexture(GameObject_P gO);
	/**
	 * \brief Loads all existing GameObjects' Textures.
	 */
	void LoadGameObjectTextures();
	/**
	 * \brief Runs Update() on all GameObjects in the Scene.
	 * \param elapsedTime Time between frames.
	 */
	void UpdateGameObjects(int elapsedTime);

	/**
	 * \brief MUST BE RAN WHILE SPRITEBATCH IS ACTIVE: Draws all GameObjects in the Scene.
	 */
	void DrawGameObjects();

	/**
	 * \brief Finds the first GameObject of Type T in the scene.
	 * \tparam T Type of Object to find in the scene.
	 * \return The GameObject if found, nullptr if not.
	 */
	template <class T>
	T* GetGameObjectOfType()
	{
		for (GameObject_P gO : _gameObjects)
		{
			auto obj = dynamic_cast<T*>(gO);
			if (obj != nullptr)
				return obj;
		}

		return nullptr;
	}

	/**
	 * \brief Finds all GameObjects of Type T in the scene.
	 * \tparam T Type of Object to find in the scene.
	 * \return List of GameObjects found.
	 */
	template <class T>
	vector<T*> GetGameObjectsOfType()
	{
		vector<T*> objects = vector<T*>();

		for (GameObject_P gO : _gameObjects)
		{
			auto obj = dynamic_cast<T*>(gO);
			if (obj != nullptr)
				objects.push_back(obj);
		}

		return objects;
	}

private:
	RenderQueue _renderQueue;
	vector<GameObject_P> _gameObjects;
	vector<Collidable_P> _collidables;
	vector<GameObject_P> _objectsToFlush;
};