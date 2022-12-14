#include "Enemy.h"
#include "Block.h"
#include <time.h>
#include "GameManager.h"
#include "Bullet.h"

Enemy::Enemy(float speed, S2D::Rect* srcRect, S2D::Vector2* position, int renderDepth, std::string textureKey)
	: GameObject(), Collidable(this, false)
{
	MovementSpeed = speed;
	SourceRect = srcRect;
	Position = position;

	_renderDepth = renderDepth;
	_textureKey = std::move(textureKey);
}

Enemy::~Enemy()
{
	delete Position;
	delete Texture;
	delete SourceRect;

	for (auto& anim : _animations)
	{
		delete anim.second;
	}
	_animations.clear();
}

void Enemy::Update(int elapsedTime)
{
	S2D::Vector2 tempPos = *Position;

	switch (_currentDirection)
	{
	case Direction::Up:
		Position->Y -= MovementSpeed * elapsedTime;
		break;
	case Direction::Down:
		Position->Y += MovementSpeed * elapsedTime;
		break;
	case Direction::Left:
		Position->X -= MovementSpeed * elapsedTime;
		break;
	case Direction::Right:
		Position->X += MovementSpeed * elapsedTime;
		break;
	default:
		break;
	}

	if (Position->X + static_cast<float>(SourceRect->Width) > static_cast<float>(S2D::Graphics::GetViewportWidth()))
	{
		Position->X = 0;
	}
	if (Position->X < 0)
	{
		Position->X = static_cast<float>(S2D::Graphics::GetViewportWidth() - SourceRect->Width);
	}

	if (Position->Y + static_cast<float>(SourceRect->Height) > static_cast<float>(S2D::Graphics::GetViewportHeight()))
	{
		Position->Y = 0;
	}
	if (Position->Y < 0)
	{
		Position->Y = static_cast<float>(S2D::Graphics::GetViewportHeight() - SourceRect->Height);
	}

	auto collider = GameManager::GameObjectManager.HasGameObjectCollided(this);
	if (collider && !dynamic_cast<Collidable*>(collider)->IsTrigger())
	{
		Position->X = tempPos.X;
		Position->Y = tempPos.Y;
	}

	timer += elapsedTime;
	if (timer >= rndTime)
	{
		RandomizeDirection(true);
		timer = 0;

		rndTime = rand() % 2000 + 500;
	}
}

void Enemy::OnCollision(GameObject* collidedObject)
{
	if (dynamic_cast<Bullet*>(collidedObject))
		GameManager::GameObjectManager.DestroyGameObject(this);

	RandomizeDirection();
}

void Enemy::RandomizeDirection(bool ignoreLastDirection)
{
	int lastDir = static_cast<int>(_currentDirection);

	int dir = rand() % 4;

	if (!ignoreLastDirection)
	{
		while (dir == lastDir)
		{
			dir = rand() % 4;
		}
	}

	_currentDirection = static_cast<Direction>(dir);
}