#pragma once
#include "GameObject.h"
#include "Collidable.h"
#include "Animation.h"
#include "Direction.cpp"
#include <map>

class Enemy :
    public GameObject, public Collidable
{
public:
    Enemy(float speed, S2D::Rect* srcRect, S2D::Vector2* position, int renderDepth, std::string textureKey);
    ~Enemy() override;

    void Update(int elapsedTime) override;
    void OnCollision(GameObject* collidedObject) override;
    bool GetDeadStatus();
    float MovementSpeed = 0;

private:
    std::map<int, Animation*> _animations;
    Direction _currentDirection = Direction::Right;

    void RandomizeDirection(bool ignoreLastDirection = false);

    int _timer = 0;
    int _rndTime = 250;

    bool _dead = false;
	int _deadAnimInt = 5;
	int _deadTimer = 0;
};

