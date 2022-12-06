#include "Game.h"
#include "GameManager.h"
#include <sstream>
#include "Block.h"
#include "MapLoader.h"

TheGame::TheGame(int argc, char* argv[]) : Game(argc, argv) 
{														//32x24 for 32x32 sized game
	S2D::Graphics::Initialise(argc, argv, this, 1024, 768, false, 25, 25, "Game", 60);
	S2D::Input::Initialise();
	S2D::Graphics::StartGameLoop();
}

TheGame::~TheGame() = default;

void TheGame::LoadContent() 
{
	auto block = new Block(new S2D::Rect(0.0f, 0.0f, 32, 32), new S2D::Vector2(200.0f, 200.0f), 1, false, "crosscube");
	auto block2 = new Block(new S2D::Rect(0.0f, 0.0f, 12, 12), new S2D::Vector2(200.0f, 250.0f), 1, true, "MunchieInverted");
	auto pause = new PauseScreen(new S2D::Rect(0.0f, 0.0f, S2D::Graphics::GetViewportWidth(), S2D::Graphics::GetViewportHeight()), "PAUSED", 15, "Transparency");

	MapLoader loader = MapLoader();
	loader.LoadMap();

	GameManager::GameObjectManager.AddGameObject(block);
	GameManager::GameObjectManager.AddGameObject(block2);
	GameManager::GameObjectManager.AddGameObject(pause);

	GameManager::GameObjectManager.LoadGameObjectTextures();
}

void TheGame::Update(int elapsedTime)
{
	S2D::Input::KeyboardState* keyboardState = S2D::Input::Keyboard::GetState();

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
		GameManager::GameObjectManager.UpdateGameObjects(elapsedTime);
	}

	GameManager::GameObjectManager.FlushGameObjects();
}

void TheGame::Draw(int elapsedTime)
{
	S2D::SpriteBatch::BeginDraw();

#pragma region Draw
	GameManager::GameObjectManager.DrawGameObjects();
	
	if (IsGamePaused)
	{
		auto pause = GameManager::GameObjectManager.GetGameObjectOfType<PauseScreen>();
		S2D::SpriteBatch::Draw(pause->Texture, pause->SourceRect, nullptr);
	}
#pragma endregion

#pragma region DrawString
	auto plr = GameManager::GameObjectManager.GetGameObjectOfType<Player>();
	if (plr != nullptr)
		DrawString("Player X: " + to_string(plr->Position->X) + " Y: " + to_string(plr->Position->Y), S2D::Vector2(10.0f, 25.0f), S2D::Color::White);

	if (IsGamePaused)
	{
		auto pause = GameManager::GameObjectManager.GetGameObjectOfType<PauseScreen>();
		DrawString(pause->PauseText, S2D::Vector2(static_cast<float>(S2D::Graphics::GetViewportWidth()) / 2.1f,
			static_cast<float>(S2D::Graphics::GetViewportHeight()) / 2.1f), S2D::Color::Red);
	}
#pragma endregion

	S2D::SpriteBatch::EndDraw();
}

void TheGame::DrawString(string str, S2D::Vector2 position, const S2D::Color* color)
{
	std::stringstream stream;
	stream << str;

	S2D::SpriteBatch::DrawString(stream.str().c_str(), &position, color);

	stream.str(std::string());
	stream.clear();
}