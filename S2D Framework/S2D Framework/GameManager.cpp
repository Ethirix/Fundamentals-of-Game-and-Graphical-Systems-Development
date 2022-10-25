#include "GameManager.h"

GameManager::GameManager(TheGame* game)
{
	_game = game;
}

string* GameManager::FindGameObjectWithName(string name) 
{
	for (string* _name : _game->GameObjects)
	{
		if (*_name == name) 
		{
			return _name;	
		}
	}
}

void GameManager::FindGameObjectsWithName(string name)
{

}

template <typename T>
void GameManager::FindGameObjectByType(T)
{
	for (string* obj : _game->GameObjects)
	{
		if (decltype(obj) == T)
		{
			//return obj
		}
	}
}

template <typename T>
void GameManager::FindGameObjectsByType(T)
{

}
