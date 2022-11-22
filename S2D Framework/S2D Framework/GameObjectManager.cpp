#include "GameObjectManager.h"
#include "Collidable.h"

GameObjectManager::~GameObjectManager()
{
	for (GameObject_P gO : _gameObjects)
	{
		delete gO;
	}
}

void GameObjectManager::DestroyGameObject(GameObject_P gO)
{
	for (GameObject_P gO_P : _gameObjects)
	{
		if (gO_P == gO)
		{
			delete gO_P;
		}

		gO = nullptr;
	}
}

void GameObjectManager::AddGameObject(GameObject_P gO)
{
	_gameObjects.push_back(gO);
}

bool GameObjectManager::HasGameObjectCollided(GameObject_P gO)
{
	Collidable* gOCollider = dynamic_cast<Collidable*>(gO);

	if (gOCollider == nullptr)
	{
		return false;
	}

	for (GameObject_P gameObject : _gameObjects)
	{
		Collidable* col = dynamic_cast<Collidable*>(gameObject);

		if (col != nullptr)
		{
			if (!col->IsTrigger())
			{
				if (gOCollider->IsCollided(gameObject))
				{
					return true;
				}
			}
		}
	}

	return false;
}

void GameObjectManager::UpdateGameObjects(int elapsedTime)
{
	for (GameObject_P gO : _gameObjects)
	{
		gO->Update(elapsedTime);
	}
}