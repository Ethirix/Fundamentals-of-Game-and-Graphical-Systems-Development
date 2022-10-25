#include "Game.h"
#include <sstream>

TheGame::TheGame(int argc, char* argv[]) : Game(argc, argv) 
{
	Graphics::Initialise(argc, argv, this, 1024, 768, false, 25, 25, "Game", 60);
	Input::Initialise();
	Graphics::StartGameLoop();
}

TheGame::~TheGame() = default;

void TheGame::LoadContent() 
{
	_player.Texture->Load("Textures/Pacman.tga", false);
}

void TheGame::Update(int elapsedTime)
{
	_player.Update(elapsedTime);
}

void TheGame::Draw(int elapsedTime)
{
	std::stringstream stream;
	stream << "Player X: " << _player.Position->X << " Y: " << _player.Position->Y;

	SpriteBatch::BeginDraw();
	SpriteBatch::Draw(_player.Texture, _player.Position, _player.SourceRect);



	SpriteBatch::DrawString(stream.str().c_str(), new Vector2(10.0f, 25.0f), Color::Green);
	SpriteBatch::EndDraw();
}