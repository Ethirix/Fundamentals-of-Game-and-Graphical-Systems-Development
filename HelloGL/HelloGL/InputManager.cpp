#include "InputManager.h"
#include <algorithm>

void InputManager::SetKeyDown(Keys::Keys key)
{
	if (std::any_of(_keysDown.begin(), _keysDown.end(),
		[key](Keys::Keys k) { return key == k; }))
		return;

	_keysDown.emplace_back(key);
}

void InputManager::SetKeyUp(Keys::Keys key)
{
	for(unsigned int i = 0; i < _keysDown.size(); i++)
	{
		if (_keysDown[i] == key)
		{
			_keysDown.erase(_keysDown.begin() + i);
			break;
		}
	}
}

void InputManager::SetSpecialKeyDown(Keys::SpecialKeys key)
{
	if (std::any_of(_specialKeysDown.begin(), _specialKeysDown.end(),
		[key](Keys::SpecialKeys k) { return key == k; }))
		return;

	_specialKeysDown.emplace_back(key);
}

void InputManager::SetSpecialKeyUp(Keys::SpecialKeys key)
{
	for(unsigned int i = 0; i < _specialKeysDown.size(); i++)
	{
		if (_specialKeysDown[i] == key)
		{
			_specialKeysDown.erase(_specialKeysDown.begin() + i);
			break;
		}
	}
}

void InputManager::SetMouseButtonDown(Keys::MouseButtons key)
{
	if (std::any_of(_mouseButtonsDown.begin(), _mouseButtonsDown.end(),
		[key](Keys::MouseButtons k) { return key == k; }))
		return;

	_mouseButtonsDown.emplace_back(key);
}

void InputManager::SetMouseButtonUp(Keys::MouseButtons key)
{
	for(unsigned int i = 0; i < _mouseButtonsDown.size(); i++)
	{
		if (_mouseButtonsDown[i] == key)
		{
			_mouseButtonsDown.erase(_mouseButtonsDown.begin() + i);
			break;
		}
	}
}

void InputManager::SetCursorPosition(Vector2 pos, Keys::MouseMovement type)
{
	_mouseMovementType = type;

	if (pos == _cursorPosition)
		_mouseMovementType = Keys::MouseMovement::NONE;
	else
		_cursorPosition = pos;
}

bool InputManager::IsKeyDown(Keys::Keys key)
{
	return std::any_of(_keysDown.begin(), _keysDown.end(), 
		[key](Keys::Keys k){ return key == k; });
}

bool InputManager::IsSpecialKeyDown(Keys::SpecialKeys key)
{
	return std::any_of(_specialKeysDown.begin(), _specialKeysDown.end(), 
		[key](Keys::SpecialKeys k){ return key == k; });
}

bool InputManager::IsMouseButtonDown(Keys::MouseButtons key)
{
	return std::any_of(_mouseButtonsDown.begin(), _mouseButtonsDown.end(), 
		[key](Keys::MouseButtons k){ return key == k; });
}

Vector2 InputManager::GetCursorPosition()
{
	return _cursorPosition;
}

Keys::MouseMovement InputManager::GetMouseMovementType()
{
	return _mouseMovementType;
}