#include "Player.h"

#include <utility>
#include "GameManager.h"

Player::Player(float speed, Rect* srcRect, Vector2* position, int renderDepth, std::string textureKey) 
	: GameObject(), Collidable(this, false)
{
	MovementSpeed = speed;
	SourceRect = srcRect;
	Position = position;

	_animations[Direction::Down] = new Animation(250, 2, Vector2(0, 32), Vector2(32, 32));
	_animations[Direction::Up] = new Animation(250, 2, Vector2(0, 96), Vector2(32, 32));
	_animations[Direction::Left] = new Animation(250, 2, Vector2(0, 64), Vector2(32, 32));
	_animations[Direction::Right] = new Animation(250, 2, Vector2(0, 0), Vector2(32, 32));

	_renderDepth = renderDepth;
	_textureKey = std::move(textureKey);
}

Player::~Player()
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

void Player::Update(int elapsedTime)
{
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();

#pragma region UpdateAnimations
	for (auto& anim : _animations)
	{
		anim.second->Update(elapsedTime);
	}
#pragma endregion

#pragma region GetInput
	if (keyboardState->IsKeyDown(Input::Keys::W))
	{
		_lastInput = Input::Keys::W;
		_currentInput = Input::Keys::W;
	}
	if (keyboardState->IsKeyDown(Input::Keys::S))
	{
		_lastInput = Input::Keys::S;
		_currentInput = Input::Keys::S;
	}
	if (keyboardState->IsKeyDown(Input::Keys::A))
	{
		_lastInput = Input::Keys::A;
		_currentInput = Input::Keys::A;
	}
	if (keyboardState->IsKeyDown(Input::Keys::D))
	{
		_lastInput = Input::Keys::D;
		_currentInput = Input::Keys::D;
	}
#pragma endregion

#pragma region Movement
	Vector2 tempPos = *Position;

	switch (_currentInput)
	{
	case Input::Keys::A:
		Position->X -= MovementSpeed * elapsedTime;
		break;
	case Input::Keys::W:
		Position->Y -= MovementSpeed * elapsedTime;
		break;
	case Input::Keys::S:
		Position->Y += MovementSpeed * elapsedTime;
		break;
	case Input::Keys::D:
		Position->X += MovementSpeed * elapsedTime;
		break;
	default:
		break;
	}

	auto collider = GameManager::GameObjectManager.HasGameObjectCollided(this);

	if (collider && !dynamic_cast<Collidable*>(collider)->IsTrigger()) 
	{
		Position->X = tempPos.X;
		Position->Y = tempPos.Y;
	}

	_currentInput = Input::Keys::RIGHTCONTROL;
#pragma endregion

#pragma region Animation
	auto currentDirection = Direction::Right;
	switch (_lastInput)
	{
	case Input::Keys::A:
		currentDirection = Direction::Left;
		break;
	case Input::Keys::W:
		currentDirection = Direction::Up;
		break;
	case Input::Keys::S:
		currentDirection = Direction::Down;
		break;
	case Input::Keys::D:
	default:
		currentDirection = Direction::Right;
		break;
	}
	
	SourceRect = _animations[currentDirection]->SourceRect;
#pragma endregion

#pragma region ScreenWrap
	if (Position->X + static_cast<float>(SourceRect->Width) > static_cast<float>(Graphics::GetViewportWidth()))
	{
		Position->X = 0;
	}
	if (Position->X < 0)
	{
		Position->X = static_cast<float>(Graphics::GetViewportWidth() - SourceRect->Width);
	}

	if (Position->Y + static_cast<float>(SourceRect->Height) > static_cast<float>(Graphics::GetViewportHeight()))
	{
		Position->Y = 0;
	}
	if (Position->Y < 0)
	{
		Position->Y = static_cast<float>(Graphics::GetViewportHeight() - SourceRect->Height);
	}
#pragma endregion
}

void Player::OnCollision(GameObject* collidedObject)
{
}