#include "WallBreakingPowerup.h"

#include "GameManager.h"
#include "Player.h"

WallBreakingPowerup::WallBreakingPowerup(S2D::Rect* srcRect, S2D::Vector2* position, int renderDepth, std::string textureKey)
	: GameObject(), Collidable(this, false)
{
	Position = position;
	SourceRect = srcRect;
	_renderDepth = renderDepth;
	_textureKey = std::move(textureKey);
}

WallBreakingPowerup::~WallBreakingPowerup()
{
	delete Position;
	delete Texture;
	delete SourceRect;
}

void WallBreakingPowerup::Update(int elapsedTime)
{
}

void WallBreakingPowerup::OnCollision(GameObject* collidedObject)
{
	if (dynamic_cast<Player*>(collidedObject))
	{
		GameManager::GameObjectManager.DestroyGameObject(this);
	}
}



