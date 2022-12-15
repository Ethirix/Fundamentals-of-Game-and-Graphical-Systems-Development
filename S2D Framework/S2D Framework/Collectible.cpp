#include "Collectible.h"

#include "GameManager.h"
#include "Player.h"

Collectible::Collectible(int score, S2D::Rect* srcRect, S2D::Vector2* position, int renderDepth, std::string textureKey)
	: GameObject(), Collidable(this, false)
{
	Position = position;
	SourceRect = srcRect;
	_renderDepth = renderDepth;
	_textureKey = std::move(textureKey);

	_score = score;
}

Collectible::~Collectible()
{
	delete Position;
	delete SourceRect;
	delete Texture;
}

void Collectible::Update(int elapsedTime)
{
}

void Collectible::OnCollision(GameObject* collidedObject)
{
	if (dynamic_cast<Player*>(collidedObject))
	{
		GameManager::GameObjectManager.DestroyGameObject(this);
	}
}

int Collectible::GetScore()
{
	return _score;
}



