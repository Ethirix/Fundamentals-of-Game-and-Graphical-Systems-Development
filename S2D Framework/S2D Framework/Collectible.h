#pragma once
#include "Collidable.h"
#include "GameObject.h"
class Collectible :
    public GameObject, public Collidable
{
public:
    Collectible(int score, S2D::Rect* srcRect, S2D::Vector2* position, int renderDepth, std::string textureKey);
    ~Collectible() override;

    void Update(int elapsedTime) override;
    void OnCollision(GameObject* collidedObject) override;

    int GetScore();

private:
    int _score;
};

