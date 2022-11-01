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
	_pause.Texture->Load("Textures/Transparency.png", false);
}

void TheGame::Update(int elapsedTime)
{
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();

#pragma region Pause
	if (keyboardState->IsKeyDown(_pauseKey) && !_isPauseKeyDown)
	{
		IsGamePaused = !IsGamePaused;
		_isPauseKeyDown = true;
	}

	if (keyboardState->IsKeyUp(_pauseKey))
	{
		_isPauseKeyDown = false;
	}
#pragma endregion

	if (!IsGamePaused)
	{
		_player.Update(elapsedTime);
	}
}

void TheGame::Draw(int elapsedTime)
{
	SpriteBatch::BeginDraw();

#pragma region Draw
	SpriteBatch::Draw(_player.Texture, _player.Position, _player.SourceRect);
	
	if (IsGamePaused)
	{
		SpriteBatch::Draw(_pause.Texture, _pause.SourceRect, nullptr);
	}
#pragma endregion

#pragma region DrawString
	DrawString("Player X: " + to_string(_player.Position->X) + " Y: " + to_string(_player.Position->Y), Vector2(10.0f, 25.0f), Color::Green);
	
	if (IsGamePaused)
	{
		DrawString(_pause.PauseText, Vector2(Graphics::GetViewportWidth() / 2.1f, Graphics::GetViewportHeight() / 2.1f), Color::Red);
	}
#pragma endregion

	SpriteBatch::EndDraw();
}

void TheGame::DrawString(string str, Vector2 position, const Color* color)
{
	std::stringstream stream;
	stream << str;

	SpriteBatch::DrawString(stream.str().c_str(), &position, color);

	stream.str(std::string());
	stream.clear();
}