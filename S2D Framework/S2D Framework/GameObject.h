#pragma once

#include "S2D/S2D.h"
#include <string>

class GameObject
{
public:
	virtual ~GameObject() = default;
	virtual void Update(int elapsedTime);

	string* Name{};
	S2D::Vector2* Position{};
	S2D::Texture2D* Texture{};
	S2D::Rect* SourceRect{};
};