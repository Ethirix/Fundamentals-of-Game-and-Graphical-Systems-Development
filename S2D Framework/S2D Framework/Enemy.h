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
    float MovementSpeed = 0;

private:
    std::map<Direction, Animation*> _animations;
    Direction _currentDirection = Direction::Right;

    void RandomizeDirection(bool ignoreLastDirection = false);

    int timer;
    int rndTime = 250;
};

