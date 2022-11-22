#include "Block.h"

#include "GameManager.h"

Block::Block(S2D::Rect* srcRect, S2D::Vector2* position, bool isATrigger)
	: GameObject(), Collidable(this, isATrigger)
{
	Position = position;
	SourceRect = srcRect;
}

Block::~Block()
{
	delete Position;
	delete SourceRect;
	delete Texture;
}

void Block::Update(int elapsedTime)
{
}

void Block::OnCollision(GameObject* collidedObject)
{
	GameManager::GameObjectManager.DestroyGameObject(this);
}
