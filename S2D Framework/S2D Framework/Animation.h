#pragma once

#include "S2D/S2D.h"

class Animation
{
public:
	/**
	 * \brief Creates a base Animation with no data.
	 */
	Animation();
	/**
	 * \brief Creates an animation with data.
	 * \param updateTime Time between animation frames.
	 * \param animationCount How many times the Rect will move across to get the next animation frame.
	 * \param rectStartPosition Start position of the Rect on the Textures.
	 * \param rectSize Size of the Rect.
	 */
	Animation(int updateTime, int animationCount, S2D::Vector2 rectStartPosition, S2D::Vector2 rectSize);
	~Animation();

	/**
	 * \brief Updates the Animation Timer
	 * \param elapsedTime Time to add to the animation timer.
	 */
	void Update(int elapsedTime);

	/**
	 * \brief Gets the Update Time
	 * \return The update time.
	 */
	int GetUpdateTime();

	/**
	 * \brief The Rect of the Animation
	 */
	S2D::Rect* SourceRect;
private:
	S2D::Vector2 _rectSize;
	S2D::Vector2 _rectStartPosition;
	int _time = 0;
	int _updateTime = 0;

	int _animationFrame = 0;
	int _animationCount = 0;
};