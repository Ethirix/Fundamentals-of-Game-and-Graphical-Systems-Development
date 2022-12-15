#include "Game.h"
#include "GameManager.h"
#include <sstream>
#include "Block.h"
#include "Collectible.h"
#include "MapLoader.h"
#include "Enemy.h"

TheGame::TheGame(int argc, char* argv[]) : Game(argc, argv) 
{
	S2D::Audio::Initialise();								//32x24 for 32x32 sized game
	S2D::Graphics::Initialise(argc, argv, this, 1024, 768, false, 25, 25, "Game", 60);
	S2D::Input::Initialise();
	S2D::Graphics::StartGameLoop();
}

TheGame::~TheGame() = default;

void TheGame::LoadContent() 
{
	auto pause = new PauseScreen(new S2D::Rect(0.0f, 0.0f, S2D::Graphics::GetViewportWidth(), S2D::Graphics::GetViewportHeight()), "PAUSED", 15, "Transparency");

	MapLoader loader = MapLoader();
	loader.LoadMap();

	GameManager::GameObjectManager.AddGameObject(pause);
	GameManager::GameObjectManager.LoadGameObjectTextures();
}

void TheGame::Update(int elapsedTime)
{
	S2D::Input::KeyboardState* keyboardState = S2D::Input::Keyboard::GetState();

	oneSecondTimer += elapsedTime;
	if (oneSecondTimer >= 1000)
	{
		srand(time(NULL));
		oneSecondTimer = 0;
	}

#pragma region Pause
	if (keyboardState->IsKeyDown(_pauseKey) && !_isPauseKeyDown)
	{
		IsGamePaused = !IsGamePaused;
		_isPauseKeyDown = true;
	}

	if (GameManager::GameObjectManager.GetGameObjectOfType<Player>()->GetDeadState())
	{
		IsGamePaused = true;
	}
	if (GameManager::GameObjectManager.GetGameObjectsOfType<Enemy>().empty() && GameManager::GameObjectManager.GetGameObjectsOfType<Collectible>().empty())
	{
		_win = true;
		IsGamePaused = true;
	}

	if (keyboardState->IsKeyUp(_pauseKey))
	{
		_isPauseKeyDown = false;
	}

#pragma endregion

	//If Game isn't paused, run Update() on all GameObjects.
	if (!IsGamePaused)
	{
		GameManager::GameObjectManager.UpdateGameObjects(elapsedTime);
	}
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
	Player* plr = GameManager::GameObjectManager.GetGameObjectOfType<Player>();
	if (plr != nullptr)
	{
		DrawString("Player X: " + to_string(plr->Position->X) + " Y: " + to_string(plr->Position->Y), S2D::Vector2(10.0f, 25.0f), S2D::Color::White);
		DrawString("Score: " + to_string(plr->GetScore()), S2D::Vector2(10, S2D::Graphics::GetViewportHeight() - 10), S2D::Color::White);
	}

	//Checks conditions for what text to display based on Game state.
	if (IsGamePaused && !plr->GetDeadState() && !_win)
	{
		auto pause = GameManager::GameObjectManager.GetGameObjectOfType<PauseScreen>();
		DrawString(pause->PauseText, S2D::Vector2(static_cast<float>(S2D::Graphics::GetViewportWidth()) / 2.1f,
			static_cast<float>(S2D::Graphics::GetViewportHeight()) / 2.1f), S2D::Color::Red);
	}
	else if (IsGamePaused && plr->GetDeadState() && !_win)
	{
		DrawString("YOU ARE DEAD", S2D::Vector2(static_cast<float>(S2D::Graphics::GetViewportWidth()) / 2.25f,
			static_cast<float>(S2D::Graphics::GetViewportHeight()) / 2.1f), S2D::Color::Red);
	}
	else if (IsGamePaused && _win)
	{
		DrawString("YOU WIN" ,S2D::Vector2(static_cast<float>(S2D::Graphics::GetViewportWidth()) / 2.3f,
			static_cast<float>(S2D::Graphics::GetViewportHeight()) / 2.1f), S2D::Color::Green);
	}
#pragma endregion

	S2D::SpriteBatch::EndDraw();

	GameManager::GameObjectManager.FlushGameObjects();
}

void TheGame::DrawString(string str, S2D::Vector2 position, const S2D::Color* color)
{
	std::stringstream stream;
	stream << str;

	S2D::SpriteBatch::DrawString(stream.str().c_str(), &position, color);

	stream.str(std::string());
	stream.clear();
}