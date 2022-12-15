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
	/**
	 * \brief Creates the Game.
	 * \param argc [UNKNOWN]
	 * \param argv [UNKNOWN]
	 */
	TheGame(int argc, char* argv[]);
	virtual ~TheGame();

	/**
	 * \brief Loads the Content before Update and Draw are called.
	 */
	void LoadContent() override;
	/**
	 * \brief Runs all code related to GameObjects before Draw().
	 * \param elapsedTime Time between each frame.
	 */
	void Update(int elapsedTime) override;
	/**
	 * \brief Draws the new Frame.
	 * \param elapsedTime Time between each frame.
	 */
	void Draw(int elapsedTime) override;

	/**
	 * \brief Game Paused flag.
	 */
	bool IsGamePaused = false;
private:
	S2D::Input::Keys _pauseKey = S2D::Input::Keys::ESCAPE;
	bool _isPauseKeyDown = false;
	bool _win = false;

	void DrawString(string str, S2D::Vector2 position, const S2D::Color* color);
	int oneSecondTimer = 0;
};