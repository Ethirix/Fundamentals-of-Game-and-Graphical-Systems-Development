#include "PauseScreen.h"

PauseScreen::PauseScreen(Rect* srcRect, string pauseText)
{
	SourceRect = srcRect;
	PauseText = pauseText;
}

PauseScreen::~PauseScreen()
{
	delete Position;
	delete Texture;
	delete SourceRect;
}