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

		_animations[static_cast<int>(Direction::Down)] = new Animation(250, 3, S2D::Vector2(0, 32*2), S2D::Vector2(7*2, 16*2));
		_animations[static_cast<int>(Direction::Up)] = new Animation(250, 3, S2D::Vector2(0, 48*2), S2D::Vector2(7*2, 16*2));
		_animations[static_cast<int>(Direction::Left)] = new Animation(250, 3, S2D::Vector2(0, 0), S2D::Vector2(12*2, 16*2));
		_animations[static_cast<int>(Direction::Right)] = new Animation(250, 3, S2D::Vector2(0, 16*2), S2D::Vector2(12*2, 16*2));
		_animations[5] = new Animation(200, 1, S2D::Vector2(21*2, 32*2), S2D::Vector2(9*2, 13*2));
		_animations[6] = new Animation(200, 1, S2D::Vector2(30*2, 32*2), S2D::Vector2(9*2, 13*2));
		_animations[7] = new Animation(200, 1, S2D::Vector2(21*2, 45*2), S2D::Vector2(19*2, 15*2));

	_renderDepth = renderDepth;
	_textureKey = std::move(textureKey);
}

Enemy::~Enemy()
{
	delete Position;
	delete Texture;
	delete SourceRect;
}

void Enemy::Update(int elapsedTime)
{
	if (_dead)
	{
		if (_deadAnimInt < 8)
		{
			_deadTimer += elapsedTime;
			if (_deadTimer >= _animations[_deadAnimInt]->GetUpdateTime())
			{
				SourceRect = _animations[_deadAnimInt]->SourceRect;
				_deadTimer = 0;
				_deadAnimInt++;
			}
		}
		else
		{
			GameManager::GameObjectManager.DestroyGameObject(this);
		}
		return;
	}

	for (auto& anim : _animations)
	{
		if (anim.first == 5 || anim.first == 6 || anim.first == 7)
			continue;

		anim.second->Update(elapsedTime);
	}

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

	_timer += elapsedTime;
	if (_timer >= _rndTime)
	{
		RandomizeDirection(true);
		_timer = 0;

		_rndTime = rand() % 2000 + 500;
	}

	SourceRect = _animations[static_cast<int>(_currentDirection)]->SourceRect;
}

void Enemy::OnCollision(GameObject* collidedObject)
{
	if (dynamic_cast<Bullet*>(collidedObject))
		_dead = true;

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

bool Enemy::GetDeadStatus()
{
	return _dead;
}
