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



class TheGame : public S2D::Game 
{
public:
	TheGame(int argc, char* argv[]);
	virtual ~TheGame();

	void LoadContent() override;
	void Update(int elapsedTime) override;
	void Draw(int elapsedTime) override;

	bool IsGamePaused = false;
private:
	S2D::Input::Keys _pauseKey = S2D::Input::Keys::ESCAPE;
	bool _isPauseKeyDown = false;

	void DrawString(string str, S2D::Vector2 position, const S2D::Color* color);
	int oneSecondTimer = 0;
};