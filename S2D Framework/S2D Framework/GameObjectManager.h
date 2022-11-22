#pragma once
#include <vector>
#include "GameObject.h"
#include "Player.h"

typedef GameObject* GameObject_P;
typedef Collidable* Collidable_P;

class GameObjectManager
{
public:
	~GameObjectManager();

	void AddGameObject(GameObject_P gO);
	void DestroyGameObject(GameObject_P gO);
	void FlushGameObjects();
	GameObject_P HasGameObjectCollided(GameObject_P gO);

	void UpdateGameObjects(int elapsedTime);
	void DrawGameObjects();

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

	template <class T>
	vector<T*> GetGameObjectsOfType()
	{
		vector<T*> objects;

		for (GameObject_P gO : _gameObjects)
		{
			auto obj = dynamic_cast<T*>(gO);
			if (obj != nullptr)
				objects.push_back(obj);
		}

		return objects;
	}

private:
	vector<GameObject_P> _gameObjects;
	vector<Collidable_P> _collidables;
	vector<GameObject_P> _objectsToFlush;
};

