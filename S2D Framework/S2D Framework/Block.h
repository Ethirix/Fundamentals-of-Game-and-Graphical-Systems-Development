#pragma once

#include "Collidable.h"
#include "S2D/S2D.h"

class Block :
    public GameObject, public Collidable
{
public:
    Block(S2D::Rect* srcRect, S2D::Vector2* position, int renderDepth, bool isATrigger, std::string textureKey);
    ~Block() override;

    void Update(int elapsedTime) override;
    void OnCollision(GameObject* collidedObject) override;
};