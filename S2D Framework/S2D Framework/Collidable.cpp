#include "Collidable.h"

Collidable::Collidable(GameObject* selfObject) : isTrigger(false), self(selfObject) {}
Collidable::Collidable(GameObject* selfObject, bool isATrigger) : isTrigger(isATrigger), self(selfObject) {}

bool Collidable::IsCollided(GameObject* objectToCheck)
{
	if (self->Position->Y + static_cast<float>(self->SourceRect->Height) < objectToCheck->Position->Y)
		return false;

	if (self->Position->Y > objectToCheck->Position->Y + static_cast<float>(objectToCheck->SourceRect->Height))
		return false;

	if (self->Position->X + static_cast<float>(self->SourceRect->Width) < objectToCheck->Position->X)
		return false;

	if (self->Position->X > objectToCheck->Position->X + static_cast<float>(objectToCheck->SourceRect->Width))
		return false;

	return true;
}


bool Collidable::IsTrigger()
{
	return isTrigger;
}