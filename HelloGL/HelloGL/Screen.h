#pragma once
#include "Vector2.h"
class Screen
{
public:
	static Vector2 GetResolution()
	{
		return _resolution;
	}

	static void SetResolution(int x, int y)
	{
		_resolution.X = x;
		_resolution.Y = y;
	}

private:
	inline static Vector2 _resolution = Vector2();
};

