#pragma once

#include <map>

#include "Animation.h"
#include "GameObject.h"
#include "S2D/S2D.h"
#include "Direction.cpp"
#include "Collidable.h"



class Player : public GameObject, public Collidable
{
public:
	Player(float speed, S2D::Rect* srcRect, S2D::Vector2* position, int renderDepth, std::string textureKey);
	~Player() override;

	void Update(int elapsedTime) override;
	void OnCollision(GameObject* collidedObject) override;
	float MovementSpeed = 0;

private:
	S2D::Input::Keys _currentInput = S2D::Input::Keys::D;
	S2D::Input::Keys _lastInput = S2D::Input::Keys::RIGHTCONTROL;
	int _frame = 0;

	map<Direction, Animation*> _animations;
};