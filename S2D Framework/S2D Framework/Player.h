#pragma once

#include <map>

#include "Animation.h"
#include "GameObject.h"
#include "S2D/S2D.h"
#include "Collidable.h"

class Player : public GameObject, public Collidable
{
public:
	Player(float speed, S2D::Rect* srcRect, S2D::Vector2* position, int renderDepth, std::string textureKey);
	~Player() override;

	void Update(int elapsedTime) override;
	void OnCollision(GameObject* collidedObject) override;
	bool GetDeadState();
	int GetScore();
	float MovementSpeed = 0;

private:
	S2D::Input::Keys _currentInput = S2D::Input::Keys::D;
	S2D::Input::Keys _lastInput = S2D::Input::Keys::RIGHTCONTROL;

	bool _dead = false;
	int _deadAnimInt = 5;
	int _deadTimer = 0;

	map<int, Animation*> _animations;
	int _fireRate = 250;
	int _timer = 0;
	int _score = 0;

	S2D::SoundEffect* _deadSFX = new S2D::SoundEffect(false, 1, 0.5);
	S2D::SoundEffect* _shootSFX = new S2D::SoundEffect(false, 1, 1);
};