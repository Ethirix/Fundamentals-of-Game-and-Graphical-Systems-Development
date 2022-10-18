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
using namespace S2D;

class TheGame : public S2D::Game
{

public:
	TheGame(int argc, char* argv[]);
	virtual ~TheGame();

	void virtual LoadContent();
	void virtual Update(int elapsedTime);
	void virtual Draw(int elapsedTime);

private:
	Player _player;
};