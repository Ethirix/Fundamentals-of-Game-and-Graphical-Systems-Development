#pragma once
#include "GameObject.h"
#include "Collidable.h"
#include "string"
#include "Direction.cpp"

class Bullet :
    public GameObject, public Collidable
{
public:
    Bullet(float speed, Direction movementDirection, S2D::Rect* srcRect, S2D::Vector2* position, int renderDepth, std::string textureKey);
    ~Bullet();

    void Update(int elapsedTime) override;
    void OnCollision(GameObject* collidedObject) override;

    float MovementSpeed = 0;
private:
    Direction _movementDirection = Direction::Right;
    int bulletTimeout = 1000;
    int timer = 0;
};

