#include "Player.h"

#include <utility>
#include "GameManager.h"
#include "Block.h"
#include "Enemy.h"
#include "Bullet.h"

Player::Player(float speed, S2D::Rect* srcRect, S2D::Vector2* position, int renderDepth, std::string textureKey)
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

	_deadSFX->Load("Audio/dead2.wav");
	_shootSFX->Load("Audio/shoot2.wav");
	//ANYTHING OVER 16B PCM DOESNT WORK BTW
}

Player::~Player()
{
	delete Position;
	delete Texture;
	delete SourceRect;
	delete _deadSFX;
	delete _shootSFX;
}

void Player::Update(int elapsedTime)
{
	S2D::Input::KeyboardState* keyboardState = S2D::Input::Keyboard::GetState();

#pragma region Dead

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
		return;
	}
#pragma endregion

#pragma region GetInput
	if (keyboardState->IsKeyDown(S2D::Input::Keys::W))
	{
		_lastInput = S2D::Input::Keys::W;
		_currentInput = S2D::Input::Keys::W;
	}
	if (keyboardState->IsKeyDown(S2D::Input::Keys::S))
	{
		_lastInput = S2D::Input::Keys::S;
		_currentInput = S2D::Input::Keys::S;
	}
	if (keyboardState->IsKeyDown(S2D::Input::Keys::A))
	{
		_lastInput = S2D::Input::Keys::A;
		_currentInput = S2D::Input::Keys::A;
	}
	if (keyboardState->IsKeyDown(S2D::Input::Keys::D))
	{
		_lastInput = S2D::Input::Keys::D;
		_currentInput = S2D::Input::Keys::D;
	}

	Direction currentDirection = Direction::Right;
	switch (_lastInput)
	{
	case S2D::Input::Keys::A:
		currentDirection = Direction::Left;
		break;
	case S2D::Input::Keys::W:
		currentDirection = Direction::Up;
		break;
	case S2D::Input::Keys::S:
		currentDirection = Direction::Down;
		break;
	case S2D::Input::Keys::D:
	default:
		currentDirection = Direction::Right;
		break;
	}

	if (_timer < _fireRate)
		_timer += elapsedTime;

	if (keyboardState->IsKeyDown(S2D::Input::Keys::SPACE) && _timer >= _fireRate)
	{
		Bullet* bullet = new Bullet(1.0f, currentDirection, new S2D::Rect(0, 0, 6, 6), new S2D::Vector2(Position->X + SourceRect->Width / 2, Position->Y + SourceRect->Height / 2), 1, "bullet");
		S2D::Audio::Play(_shootSFX);
		GameManager::GameObjectManager.AddGameObject(bullet);
		GameManager::GameObjectManager.LoadGameObjectTexture(bullet);
		_timer = 0;
	}
#pragma endregion

#pragma region Movement
	S2D::Vector2 tempPos = *Position;

	switch (_currentInput)
	{
	case S2D::Input::Keys::A:
		Position->X -= MovementSpeed * elapsedTime;
		break;
	case S2D::Input::Keys::W:
		Position->Y -= MovementSpeed * elapsedTime;
		break;
	case S2D::Input::Keys::S:
		Position->Y += MovementSpeed * elapsedTime;
		break;
	case S2D::Input::Keys::D:
		Position->X += MovementSpeed * elapsedTime;
		break;
	default:
		break;
	}

#pragma region ScreenWrap
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
#pragma endregion

	auto collider = GameManager::GameObjectManager.HasGameObjectCollided(this);

	if (collider && !dynamic_cast<Collidable*>(collider)->IsTrigger()) 
	{
		Position->X = tempPos.X;
		Position->Y = tempPos.Y;
	}

	_currentInput = S2D::Input::Keys::RIGHTCONTROL;
#pragma endregion

#pragma region UpdateAnimations
	if (tempPos != *Position)
	{
		for (auto& anim : _animations)
		{
			if (anim.first == 5 || anim.first == 6 || anim.first == 7)
				continue;

			anim.second->Update(elapsedTime);
		}
	}
#pragma endregion

#pragma region Animation
	SourceRect = _animations[static_cast<int>(currentDirection)]->SourceRect;
#pragma endregion
}

void Player::OnCollision(GameObject* collidedObject)
{
	if (dynamic_cast<Block*>(collidedObject))
	{
		Block* block = dynamic_cast<Block*>(collidedObject);
		S2D::Input::KeyboardState* keyboardState = S2D::Input::Keyboard::GetState();

		if (keyboardState->IsKeyDown(S2D::Input::Keys::E))
		{
			GameManager::GameObjectManager.DestroyGameObject(block);
		}
	}
	else if (dynamic_cast<Enemy*>(collidedObject))
	{
		if (!dynamic_cast<Enemy*>(collidedObject)->GetDeadStatus() && !_dead)
		{
			_dead = true;
			S2D::Audio::Play(_deadSFX);
		}
	}
}

bool Player::GetDeadState()
{
	if (_deadAnimInt >= 8)
		return true;

	return false;
}
