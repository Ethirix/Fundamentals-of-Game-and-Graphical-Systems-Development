#include "GameObjectManager.h"
#include "Collidable.h"
#include "PauseScreen.h"
#include "TextureManager.h"

GameObjectManager::~GameObjectManager()
{
	for (GameObject_P gO : _gameObjects)
	{
		delete gO;
	}
}

void GameObjectManager::DestroyGameObject(GameObject_P gO)
{
	_objectsToFlush.push_back(gO);
}

void GameObjectManager::FlushGameObjects()
{
	for (auto gO : _objectsToFlush)
	{
		for (int i = 0; i < _gameObjects.size(); ++i)
		{
			if (_gameObjects[i] == gO)
				_gameObjects.erase(_gameObjects.begin() + i);
		}

		auto col = dynamic_cast<Collidable_P>(gO);

		if (col)
		{
			for (int i = 0; i < _collidables.size(); ++i)
			{
				if (_collidables[i] == col)
					_collidables.erase(_collidables.begin() + i);
			}
		}

		delete gO;
	}

	_objectsToFlush.clear();
}

void GameObjectManager::AddGameObject(GameObject_P gO)
{
	_gameObjects.push_back(gO);

	auto collidable = dynamic_cast<Collidable_P>(gO);
	if (collidable != nullptr)
		_collidables.push_back(collidable);
}

GameObject* GameObjectManager::HasGameObjectCollided(GameObject_P gO)
{
	auto gOCollider = dynamic_cast<Collidable_P>(gO);

	if (gOCollider == nullptr)
		return nullptr;

	for (Collidable_P collidable : _collidables)
	{
		if (gOCollider == collidable)
			continue;

		if (gOCollider->IsCollided(collidable->GetSelf()))
		{
			collidable->OnCollision(gOCollider->GetSelf());
			gOCollider->OnCollision(collidable->GetSelf());

			return collidable->GetSelf();
		}
	}

	return nullptr;
}

void GameObjectManager::LoadGameObjectTextures()
{
	TextureManager::InitializeTextureManager();

	for (GameObject_P gO : _gameObjects)
	{
		gO->Load();
	}
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
		if (!gO || dynamic_cast<PauseScreen*>(gO) != nullptr)
			continue;

		SpriteBatch::Draw(gO->Texture, gO->Position, gO->SourceRect);
	}
}