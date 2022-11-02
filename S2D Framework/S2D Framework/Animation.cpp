#include "Animation.h"

Animation::Animation() = default;

Animation::Animation(int updateTime, int animationCount, S2D::Vector2 rectStartPosition, S2D::Vector2 rectSize)
{
	_updateTime = updateTime;
	_animationCount = --animationCount;
	_rectSize = rectSize;
	_rectStartPosition = rectStartPosition;

	SourceRect = new S2D::Rect(_rectStartPosition.X, _rectStartPosition.Y, _rectSize.X,_rectSize.Y);
}

Animation::~Animation()
{
	delete SourceRect;
}

void Animation::Update(int elapsedTime)
{
	_time += elapsedTime;

	if (_time >= _updateTime)
	{
		_time = 0;

		++_animationFrame;
		if (_animationFrame > _animationCount)
		{
			_animationFrame = 0;
		}

		SourceRect = new S2D::Rect((_rectStartPosition.X + _rectSize.X) * _animationFrame, _rectStartPosition.Y, _rectSize.X, _rectSize.Y);
	}
}