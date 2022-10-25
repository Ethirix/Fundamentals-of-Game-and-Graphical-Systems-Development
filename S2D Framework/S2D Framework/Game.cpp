#include "Game.h"
#include <sstream>


TheGame::TheGame(int argc, char* argv[]) : S2D::Game(argc, argv) 
{
	Graphics::Initialise(argc, argv, this, 1024, 768, false, 25, 25, "Game", 60);
	Input::Initialise();
	Graphics::StartGameLoop();
}

TheGame::~TheGame()
{
	
}

void TheGame::LoadContent() 
{
	Texture2D* _plrText = new Texture2D();
	_plrText->Load("Textures/Pacman.tga", false);
	_player = Player(0.1f, new Rect(0.0f, 0.0f, 32, 32), _plrText);
	

	delete _plrText;
}

void TheGame::Update(int elapsedTime)
{

}

void TheGame::Draw(int elapsedTime)
{

}