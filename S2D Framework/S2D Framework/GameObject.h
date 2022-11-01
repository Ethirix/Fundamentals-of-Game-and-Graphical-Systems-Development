#pragma once

#include "S2D/S2D.h"
#include <string>

class GameObject
{
public:
	virtual ~GameObject() = default;
	virtual void Update(int elapsedTime);

	S2D::Vector2* Position = new S2D::Vector2(0.0f, 0.0f);
	S2D::Texture2D* Texture = new S2D::Texture2D();
	S2D::Rect* SourceRect = new S2D::Rect();
};