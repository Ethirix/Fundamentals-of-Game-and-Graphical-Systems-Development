#include "GameObjectManager.h"
#include "Collidable.h"
#include "PauseScreen.h"

GameObjectManager::~GameObjectManager()
{
	for (GameObject_P gO : _gameObjects)
	{
		delete gO;
	}
}

void GameObjectManager::DestroyGameObject(GameObject_P gO)
{
	for (GameObject_P gOp : _gameObjects)
	{
		if (gOp == gO)
		{
			delete gOp;
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

void GameObjectManager::DrawGameObjects()
{
	for (GameObject_P gO : _gameObjects)
	{
		if (dynamic_cast<PauseScreen*>(gO) != nullptr)
			continue;

		if (gO)
			SpriteBatch::Draw(gO->Texture, gO->Position, gO->SourceRect);
	}
}
