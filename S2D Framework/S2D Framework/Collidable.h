#pragma once

#include "GameObject.h"

class Collidable
{
public:
	Collidable() = default;
	Collidable(GameObject* selfObject);
	Collidable(GameObject* selfObject, bool isATrigger);
	~Collidable() = default;
	bool IsCollided(GameObject* objectToCheck);
	bool IsTrigger();
private:
	bool isTrigger;
	GameObject* self;
};