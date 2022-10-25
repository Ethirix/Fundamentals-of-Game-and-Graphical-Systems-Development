#pragma once

#include "S2D/S2D.h"
using namespace S2D;

class GameObject
{
public:
	virtual ~GameObject() = default;
	virtual void Update(int elapsedTime);

	Vector2* Position{};
	Texture2D* Texture{};
	Rect* SourceRect{};
};