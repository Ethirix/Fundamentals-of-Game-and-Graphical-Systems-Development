#pragma once

#include "GameObject.h"

using namespace S2D;

class PauseScreen : public GameObject
{
public:
	PauseScreen(Rect* srcRect, string pauseText, int renderDepth, std::string textureKey);
	~PauseScreen();

	string PauseText = "";
};

