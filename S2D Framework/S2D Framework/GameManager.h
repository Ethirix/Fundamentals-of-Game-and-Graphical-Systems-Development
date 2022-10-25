#pragma once
#include "S2D/S2D.h"
#include <string>
#include "Game.h"

class GameManager
{
private:
	TheGame* _game;

public:
	GameManager(TheGame* game);

	void FindGameObjectWithName(string name);
	void FindGameObjectsWithName(string name);

	template <typename T>
	void FindGameObjectByType(T);
	template <typename T>
	void FindGameObjectsByType(T);
};

