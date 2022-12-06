#pragma once

#include "GameObject.h"

class PauseScreen : public GameObject
{
public:
	PauseScreen(S2D::Rect* srcRect, string pauseText, int renderDepth, std::string textureKey);
	~PauseScreen();

	string PauseText = "";
};

