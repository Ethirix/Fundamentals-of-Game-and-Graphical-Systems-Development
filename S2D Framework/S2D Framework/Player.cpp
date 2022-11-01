#include "Player.h"

Player::Player(float speed, Rect* srcRect, Vector2* position)
{
	MovementSpeed = speed;
	SourceRect = srcRect;
	Position = position;

	_animations[Down] = Animation(15, 2, Vector2(0, 32), Vector2(32, 32));
	_animations[Up] = Animation(15, 2, Vector2(0, 96), Vector2(32, 32));
	_animations[Left] = Animation(15, 2, Vector2(0, 64), Vector2(32, 32));
	_animations[Right] = Animation(15, 2, Vector2(0, 0), Vector2(32, 32));
}

Player::~Player()
{
	delete Position;
	delete Texture;
	delete SourceRect;
}

void Player::Update(int elapsedTime)
{
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();

#pragma region UpdateAnimations
	for (auto& anim : _animations)
	{
		anim.second.Update();
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

	_currentInput = Input::Keys::RIGHTCONTROL;
#pragma endregion

#pragma region Animation
	Direction currentDirection = Right;
	switch (_lastInput)
	{
	case Input::Keys::A:
		currentDirection = Left;
		break;
	case Input::Keys::W:
		currentDirection = Up;
		break;
	case Input::Keys::S:
		currentDirection = Down;
		break;
	case Input::Keys::D:
	default:
		currentDirection = Right;
		break;
	}
	
	SourceRect = _animations[currentDirection].SourceRect;
#pragma endregion

#pragma region ScreenWrap
	if (Position->X + SourceRect->Width > Graphics::GetViewportWidth())
	{
		Position->X = 0;
	}
	if (Position->X < 0)
	{
		Position->X = Graphics::GetViewportWidth() - SourceRect->Width;
	}

	if (Position->Y + SourceRect->Height > Graphics::GetViewportHeight())
	{
		Position->Y = 0;
	}
	if (Position->Y < 0)
	{
		Position->Y = Graphics::GetViewportHeight() - SourceRect->Height;
	}
#pragma endregion
}