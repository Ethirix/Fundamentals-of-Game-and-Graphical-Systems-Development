#pragma once

// If Windows and not in Debug, this will run without a console window
// You can use this to output information when debugging using cout or cerr
#ifdef WIN32 
	#ifndef _DEBUG
		#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	#endif
#endif

#include "S2D/S2D.h"
#include "Player.h"
#include "PauseScreen.h"

using namespace S2D;

class TheGame : public Game 
{
public:
	TheGame(int argc, char* argv[]);
	virtual ~TheGame();

	void LoadContent() override;
	void Update(int elapsedTime) override;
	void Draw(int elapsedTime) override;

	bool IsGamePaused = false;
private:
	Input::Keys _pauseKey = Input::Keys::ESCAPE;
	bool _isPauseKeyDown = false;

	void DrawString(string str, Vector2 position, const Color* color);
};