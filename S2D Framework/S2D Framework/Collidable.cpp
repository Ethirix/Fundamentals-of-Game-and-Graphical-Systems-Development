#include "Collidable.h"

Collidable::Collidable(GameObject& selfObject) : self(selfObject), isTrigger(false) {}
Collidable::Collidable(GameObject& selfObject, bool isATrigger) : self(selfObject), isTrigger(isATrigger) {}

bool Collidable::IsCollided(GameObject& objectToCheck)
{
	if (self.Position->Y + self.SourceRect->Height < objectToCheck.Position->Y)
		return false;

	if (self.Position->Y > objectToCheck.Position->Y + objectToCheck.SourceRect->Height)
		return false;

	if (self.SourceRect->Right() < objectToCheck.SourceRect->Left())
		return false;

	if (self.SourceRect->Left() > objectToCheck.SourceRect->Right())
		return false;

	return true;
}

bool Collidable::IsCollided(GameObject* objectToCheck)
{
	if (self.SourceRect->Bottom() < objectToCheck->SourceRect->Top())
		return false;

	if (self.SourceRect->Top() > objectToCheck->SourceRect->Bottom())
		return false;

	if (self.SourceRect->Right() < objectToCheck->SourceRect->Left())
		return false;

	if (self.SourceRect->Left() > objectToCheck->SourceRect->Right())
		return false;

	return true;
}


bool Collidable::IsTrigger()
{
	return isTrigger;
}