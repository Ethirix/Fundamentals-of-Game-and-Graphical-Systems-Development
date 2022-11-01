#pragma once

#include "S2D/S2D.h"

class Animation
{
public:
	Animation();
	Animation(int updateFrame, int animationCount, S2D::Vector2 rectStartPosition, S2D::Vector2 rectSize);
	~Animation();

	void Update();

	S2D::Rect* SourceRect;
private:
	S2D::Vector2 _rectSize;
	S2D::Vector2 _rectStartPosition;
	int _frameCount = 0;
	int _updateFrame = 0;

	int _animationFrame = 0;
	int _animationCount = 0;
};