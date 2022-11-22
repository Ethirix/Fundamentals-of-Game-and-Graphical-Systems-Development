#include "Collidable.h"

Collidable::Collidable(GameObject* selfObject) : _isTrigger(false), _self(selfObject) {}
Collidable::Collidable(GameObject* selfObject, bool isATrigger) : _isTrigger(isATrigger), _self(selfObject) {}

bool Collidable::IsCollided(GameObject* objectToCheck)
{
	if (_self->Position->Y + static_cast<float>(_self->SourceRect->Height) < objectToCheck->Position->Y)
		return false;

	if (_self->Position->Y > objectToCheck->Position->Y + static_cast<float>(objectToCheck->SourceRect->Height))
		return false;

	if (_self->Position->X + static_cast<float>(_self->SourceRect->Width) < objectToCheck->Position->X)
		return false;

	if (_self->Position->X > objectToCheck->Position->X + static_cast<float>(objectToCheck->SourceRect->Width))
		return false;

	return true;
}

bool Collidable::IsTrigger()
{
	return _isTrigger;
}

GameObject* Collidable::GetSelf()
{
	return _self;
}

void Collidable::OnCollision(GameObject* collidedObject) {}
