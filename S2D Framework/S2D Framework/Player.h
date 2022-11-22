#pragma once

#include <map>

#include "Animation.h"
#include "GameObject.h"
#include "S2D/S2D.h"
#include "Direction.cpp"
#include "Collidable.h"

using namespace S2D;

class Player : public GameObject, public Collidable
{
public:
	Player(float speed, Rect* srcRect, Vector2* position);
	~Player() override;

	void Update(int elapsedTime) override;
	float MovementSpeed = 0;

private:
	Input::Keys _currentInput = Input::Keys::D;
	Input::Keys _lastInput = Input::Keys::RIGHTCONTROL;
	int _frame = 0;

	map<Direction, Animation> _animations;
};