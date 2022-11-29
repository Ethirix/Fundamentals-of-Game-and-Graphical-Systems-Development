#include "PauseScreen.h"

PauseScreen::PauseScreen(Rect* srcRect, string pauseText, int renderDepth, std::string textureKey)
{
	SourceRect = srcRect;
	PauseText = pauseText;
	_renderDepth = renderDepth;
	_textureKey = textureKey;
}

PauseScreen::~PauseScreen()
{
	delete Position;
	delete Texture;
	delete SourceRect;
}