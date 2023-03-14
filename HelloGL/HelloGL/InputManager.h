#pragma once
#include <vector>

#include "InputEnums.h"
#include "Vector2.h"

class InputManager
{
public:
	void SetKeyDown(Keys::Keys key);
	void SetKeyUp(Keys::Keys key);
	void SetSpecialKeyDown(Keys::SpecialKeys key);
	void SetSpecialKeyUp(Keys::SpecialKeys key);
	void SetMouseButtonDown(Keys::MouseButtons key);
	void SetMouseButtonUp(Keys::MouseButtons key);
	void SetCursorPosition(Vector2 pos, Keys::MouseMovement type);

	bool IsKeyDown(Keys::Keys key);
	bool IsSpecialKeyDown(Keys::SpecialKeys key);
	bool IsMouseButtonDown(Keys::MouseButtons key);

	Keys::MouseMovement GetMouseMovementType();

	Vector2 GetCursorPosition();
private:
	std::vector<Keys::Keys> _keysDown;
	std::vector<Keys::SpecialKeys> _specialKeysDown;
	std::vector<Keys::MouseButtons> _mouseButtonsDown;
	Vector2 _cursorPosition;
	Keys::MouseMovement _mouseMovementType = Keys::MouseMovement::NONE;
};

