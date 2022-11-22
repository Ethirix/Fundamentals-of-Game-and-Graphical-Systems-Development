#pragma once
#include <vector>
#include "GameObject.h"

typedef GameObject* GameObject_P;

using namespace std;


class GameObjectManager
{
public:
	~GameObjectManager();

	void AddGameObject(GameObject_P gO);
	void DestroyGameObject(GameObject_P gO);
private:
	vector<GameObject_P> _gameObjects;
};

