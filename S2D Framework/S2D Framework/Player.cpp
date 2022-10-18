#pragma once
#include "Player.h"
using namespace S2D;

Player::Player(float speed, Rect* srcRect, Texture2D* texture)
{
	_movementSpeed = speed;
	_sourceRect = srcRect;
	_texture = texture;
}

Player::~Player()
{
	delete Position;
	delete _texture;
	delete _sourceRect;
	delete _movementSpeed;
}

Texture2D* Player::GetTexture()
{
	return _texture;
}

Rect* Player::GetSourceRect()
{
	return _sourceRect;
}

float* Player::GetMovementSpeed()
{
	return _movementSpeed;
}

void Player::RunMovement(Input::KeyboardState* keyboardState, float elapsedTime)
{
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

	switch (_currentInput)
	{
	case Input::Keys::A:
		Position->X -= _movementSpeed * elapsedTime;
		break;
	case Input::Keys::W:
		Position->Y -= _movementSpeed * elapsedTime;
		break;
	case Input::Keys::S:
		Position->Y += _movementSpeed * elapsedTime;
		break;
	case Input::Keys::D:
		Position->X += _movementSpeed * elapsedTime;
		break;
	default:
		break;
	}

	_currentInput = Input::Keys::RIGHTCONTROL;

	Direction currentDirection = RIGHT;

	switch (_lastInput)
	{
	case Input::Keys::A:
		currentDirection = Direction::LEFT;
		break;
	case Input::Keys::W:
		currentDirection = Direction::UP;
		break;
	case Input::Keys::S:
		currentDirection = Direction::DOWN;
		break;
	case Input::Keys::D:
		currentDirection = Direction::RIGHT;
		break;
	default:
		currentDirection = RIGHT;
		break;
	}

	_sourceRect = new Rect(32.0f * _frame, 32.0f * currentDirection, 32, 32);

	if (Position->X + _sourceRect->Width > Graphics::GetViewportWidth())
	{
		Position->X = Graphics::GetViewportWidth() - _sourceRect->Width;
	}
	if (Position->X < 0)
	{
		Position->X = 0;
	}

	if (Position->Y + _sourceRect->Height > Graphics::GetViewportHeight())
	{
		Position->Y = Graphics::GetViewportHeight() - _sourceRect->Height;
	}
	if (Position->Y < 0)
	{
		Position->Y = 0;
	}
}