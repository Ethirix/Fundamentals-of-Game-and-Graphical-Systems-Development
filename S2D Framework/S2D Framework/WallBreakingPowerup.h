#pragma once
#include "Collectible.h"
#include "GameObject.h"
class WallBreakingPowerup :
    public GameObject, public Collidable
{
public:
    WallBreakingPowerup(S2D::Rect* srcRect, S2D::Vector2* position, int renderDepth, std::string textureKey);
    ~WallBreakingPowerup() override;

    void Update(int elapsedTime) override;
    void OnCollision(GameObject* collidedObject) override;
};