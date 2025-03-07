#include "GameObjectManager.h"
#include "Collidable.h"
#include "PauseScreen.h"
#include "TextureManager.h"

GameObjectManager::GameObjectManager()
{
	_renderQueue = RenderQueue(16);
}


GameObjectManager::~GameObjectManager()
{
	for (GameObject_P gO : _gameObjects)
	{
		delete gO;
		gO = nullptr;
	}

	for (Collidable_P c : _collidables)
	{
		delete c;
		c = nullptr;
	}
}

void GameObjectManager::DestroyGameObject(GameObject_P gO)
{
	_objectsToFlush.push_back(gO);
}

void GameObjectManager::FlushGameObjects()
{
	for (auto& gO : _objectsToFlush)
	{
		for (int i = 0; i < static_cast<int>(_gameObjects.size()); ++i)
		{
			if (_gameObjects[i] == gO)
				_gameObjects.erase(_gameObjects.begin() + i);
		}

 		auto col = dynamic_cast<Collidable_P>(gO);

		if (col)
		{
			for (int i = 0; i < static_cast<int>(_collidables.size()); ++i)
			{
				if (_collidables[i] == col)
					_collidables.erase(_collidables.begin() + i);
			}
		}

		_renderQueue.Remove(gO);
	}

	for (auto& gO : _objectsToFlush)
	{
		delete gO;
	}

	_objectsToFlush.clear();
}

void GameObjectManager::AddGameObject(GameObject_P gO)
{
	_gameObjects.push_back(gO);
	_renderQueue.Add(gO);

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

void GameObjectManager::LoadGameObjectTexture(GameObject_P gO)
{
	gO->Load();
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
	for (int i = 0; i < _gameObjects.size(); i++)
	{
		_gameObjects[i]->Update(elapsedTime);
	}
}

void GameObjectManager::DrawGameObjects()
{
	for (int i = 0; i < _renderQueue.GetQueueSize(); i++)
	{
		for (auto gO : _renderQueue.RndQueue[i])
		{
			if (!gO || dynamic_cast<PauseScreen*>(gO) != nullptr)
				continue;

			S2D::SpriteBatch::Draw(gO->Texture, gO->Position, gO->SourceRect);
		}
	}
}