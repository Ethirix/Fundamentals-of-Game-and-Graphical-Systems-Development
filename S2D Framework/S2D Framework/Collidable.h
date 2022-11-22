#pragma once

#include "GameObject.h"

class Collidable
{
public:
	Collidable() = default;
	Collidable(GameObject* selfObject);
	Collidable(GameObject* selfObject, bool isATrigger);
	virtual ~Collidable() = default;
	bool IsCollided(GameObject* objectToCheck);
	bool IsTrigger();
	virtual void OnCollision(GameObject* collidedObject);
	GameObject* GetSelf();
private:
	bool _isTrigger = false;
	GameObject* _self = nullptr;
};