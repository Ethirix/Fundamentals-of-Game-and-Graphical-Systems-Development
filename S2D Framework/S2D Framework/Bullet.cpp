#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Block.h"
#include "GameManager.h"

Bullet::Bullet(float speed, Direction movementDirection, S2D::Rect* srcRect, S2D::Vector2* position, int renderDepth, std::string textureKey)
	: GameObject(), Collidable(this, false)
{
	MovementSpeed = speed;
	SourceRect = srcRect;
	Position = position;
	_movementDirection = movementDirection;
	_renderDepth = renderDepth;
	_textureKey = std::move(textureKey);
}

Bullet::~Bullet()
{
	delete Position;
	delete SourceRect;
	delete Texture;
}

void Bullet::Update(int elapsedTime)
{
	timer += elapsedTime;
	if (timer >= bulletTimeout)
	{
		GameManager::GameObjectManager.DestroyGameObject(this);
	}

	switch (_movementDirection)
	{
	case Direction::Left:
		Position->X -= MovementSpeed * elapsedTime;
		break;
	case Direction::Up:
		Position->Y -= MovementSpeed * elapsedTime;
		break;
	case Direction::Down:
		Position->Y += MovementSpeed * elapsedTime;
		break;
	case Direction::Right:
		Position->X += MovementSpeed * elapsedTime;
		break;
	default:
		break;
	}

	GameManager::GameObjectManager.HasGameObjectCollided(this);
}

void Bullet::OnCollision(GameObject* collidedObject)
{
	if (dynamic_cast<Block*>(collidedObject) || dynamic_cast<Enemy*>(collidedObject))
	{
		GameManager::GameObjectManager.DestroyGameObject(this);
	}
}