#include "Game.h"
#include "GameManager.h"
#include <sstream>
#include "Block.h"

TheGame::TheGame(int argc, char* argv[]) : Game(argc, argv) 
{
	Graphics::Initialise(argc, argv, this, 1024, 768, false, 25, 25, "Game", 60);
	Input::Initialise();
	Graphics::StartGameLoop();
}

TheGame::~TheGame() = default;

void TheGame::LoadContent() 
{
	auto block = new Block(new Rect(0.0f, 0.0f, 12, 12), new Vector2(200.0f, 200.0f), false);
	auto block2 = new Block(new Rect(0.0f, 0.0f, 12, 12), new Vector2(200.0f, 250.0f), true);
	auto plr = new Player(0.1f, new Rect(0.0f, 0.0f, 32, 32), new Vector2(100.0f, 100.0f));
	auto pause = new PauseScreen(new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight()), "PAUSED");

	block->Texture->Load("Textures/Munchie.tga", false);
	block2->Texture->Load("Textures/MunchieInverted.tga", false);
	plr->Texture->Load("Textures/Pacman.tga", false);
	pause->Texture->Load("Textures/Transparency.png", false);

	GameManager::GameObjectManager.AddGameObject(plr);
	GameManager::GameObjectManager.AddGameObject(block);
	GameManager::GameObjectManager.AddGameObject(block2);
	GameManager::GameObjectManager.AddGameObject(pause);
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
		GameManager::GameObjectManager.UpdateGameObjects(elapsedTime);
	}

	GameManager::GameObjectManager.FlushGameObjects();
}

void TheGame::Draw(int elapsedTime)
{
	SpriteBatch::BeginDraw();

#pragma region Draw
	GameManager::GameObjectManager.DrawGameObjects();
	
	if (IsGamePaused)
	{
		auto pause = GameManager::GameObjectManager.GetGameObjectOfType<PauseScreen>();
		SpriteBatch::Draw(pause->Texture, pause->SourceRect, nullptr);
	}
#pragma endregion

#pragma region DrawString
	auto plr = GameManager::GameObjectManager.GetGameObjectOfType<Player>();
	DrawString("Player X: " + to_string(plr->Position->X) + " Y: " + to_string(plr->Position->Y), Vector2(10.0f, 25.0f), Color::Green);

	if (IsGamePaused)
	{
		auto pause = GameManager::GameObjectManager.GetGameObjectOfType<PauseScreen>();
		DrawString(pause->PauseText, Vector2(static_cast<float>(Graphics::GetViewportWidth()) / 2.1f, 
			static_cast<float>(Graphics::GetViewportHeight()) / 2.1f), Color::Red);
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