#include "PauseScreen.h"

PauseScreen::PauseScreen(Rect* srcRect, string pauseText, std::string textureKey)
{
	SourceRect = srcRect;
	PauseText = pauseText;
	_textureKey = textureKey;
}

PauseScreen::~PauseScreen()
{
	delete Position;
	delete Texture;
	delete SourceRect;
}