#include "Animation.h"

Animation::Animation()
{
	SourceRect = new S2D::Rect(0, 0, 0, 0);
}

Animation::Animation(int updateTime, int animationCount, S2D::Vector2 rectStartPosition, S2D::Vector2 rectSize)
{
	_updateTime = updateTime;
	_animationCount = --animationCount;
	_rectSize = rectSize;
	_rectStartPosition = rectStartPosition;

	SourceRect = new S2D::Rect(_rectStartPosition.X, _rectStartPosition.Y, static_cast<int>(_rectSize.X), static_cast<int>(_rectSize.Y));
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

		SourceRect = new S2D::Rect((_rectStartPosition.X + _rectSize.X) * static_cast<float>(_animationFrame),
		                           _rectStartPosition.Y, static_cast<int>(_rectSize.X), static_cast<int>(_rectSize.Y));
	}
}