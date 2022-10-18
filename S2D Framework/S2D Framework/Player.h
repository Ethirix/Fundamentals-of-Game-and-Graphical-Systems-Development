#pragma once

#include "S2D/S2D.h"
using namespace S2D;

enum Direction
{
	UP = 3,
	DOWN = 1,
	LEFT = 2,
	RIGHT = 0
};

class Player
{
public:
	Player(float speed, Rect* srcRect, Texture2D* texture);
	~Player();
	
	Texture2D* GetTexture();
	Rect* GetSourceRect();
	float GetMovementSpeed();

	void RunMovement(Input::KeyboardState* keyboardState, float elapsedTime);

	Vector2* Position;
	

private:
	Texture2D* _texture;
	Rect* _sourceRect;
	float _movementSpeed;
};