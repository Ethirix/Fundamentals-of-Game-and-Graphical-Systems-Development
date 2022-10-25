#include "Animation.h"

Animation::Animation() = default;

Animation::Animation(int updateFrame, int animationCount, S2D::Vector2 rectStartPosition, S2D::Vector2 rectSize)
{
	_updateFrame = updateFrame;
	_animationCount = --animationCount;
	_rectSize = rectSize;
	_rectStartPosition = rectStartPosition;

	SourceRect = new S2D::Rect(rectStartPosition.X, rectStartPosition.Y, _rectSize.X, _rectSize.Y);
}

Animation::~Animation()
{
	delete SourceRect;
}

void Animation::Update()
{
	++_frameCount;

	if (_frameCount % _updateFrame == 0)
	{
		_frameCount = 0;

		++_animationFrame;
		if (_animationFrame > _animationCount)
		{
			_animationFrame = 0;
		}

		SourceRect = new S2D::Rect((_rectStartPosition.X + _rectSize.X) * _animationFrame, _rectStartPosition.Y, _rectSize.X, _rectSize.Y);
	}
}