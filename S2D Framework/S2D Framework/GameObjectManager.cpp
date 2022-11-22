#include "GameObjectManager.h"

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
