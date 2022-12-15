#include "MapLoader.h"
#include "GameManager.h"
#include "Enemy.h"
#include <filesystem>
#include <fstream>

#include "Collectible.h"
#include "WallBreakingPowerup.h"

void MapLoader::LoadMap()
{
	std::map<char, GameObject*> map = MapLoader::InitializeMap();
	
	if (!std::filesystem::exists(Path + "map1.txt"))
	{
		std::ofstream{ Path + "map1.txt" };
	}

	std::string line;
	int lineNo = -1;
	std::ifstream file (Path + "map1.txt");
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			lineNo += 1;
			for (int i = 0; i < line.length(); i++)
			{
				if (dynamic_cast<Block*>(map[line[i]]))
				{
					Block original = *dynamic_cast<Block*>(map[line[i]]);
					Block* block = new Block(new S2D::Rect(original.SourceRect->X, original.SourceRect->Y, original.SourceRect->Width, original.SourceRect->Height), 
						new S2D::Vector2(32 * i, 32 * lineNo), original.GetRenderDepth(), original.IsTrigger(), original.GetTextureKey());
					GameManager::GameObjectManager.AddGameObject(block);
				}
				else if (dynamic_cast<Player*>(map[line[i]]))
				{
					Player original = *dynamic_cast<Player*>(map[line[i]]);
					Player* plr = new Player(0.1f, new S2D::Rect(original.SourceRect->X, original.SourceRect->Y, original.SourceRect->Width, original.SourceRect->Height),
						new S2D::Vector2(32 * i, 32 * lineNo), original.GetRenderDepth(), original.GetTextureKey());

					GameManager::GameObjectManager.AddGameObject(plr);
				}
				else if (dynamic_cast<Enemy*>(map[line[i]]))
				{
					Enemy original = *dynamic_cast<Enemy*>(map[line[i]]);
					Enemy* enemy = new Enemy(0.1f, new S2D::Rect(original.SourceRect->X, original.SourceRect->Y, original.SourceRect->Width, original.SourceRect->Height),
						new S2D::Vector2(32 * i, 32 * lineNo), original.GetRenderDepth(), original.GetTextureKey());
					
					GameManager::GameObjectManager.AddGameObject(enemy);
				}
				else if (dynamic_cast<Collectible*>(map[line[i]]))
				{
					Collectible original = *dynamic_cast<Collectible*>(map[line[i]]);
					Collectible* collectible = new Collectible(25, new S2D::Rect(original.SourceRect->X, original.SourceRect->Y, original.SourceRect->Width, original.SourceRect->Height),
						new S2D::Vector2(32 * i, 32 * lineNo), original.GetRenderDepth(), original.GetTextureKey());

					GameManager::GameObjectManager.AddGameObject(collectible);
				}
				else if (dynamic_cast<WallBreakingPowerup*>(map[line[i]]))
				{
					WallBreakingPowerup original = *dynamic_cast<WallBreakingPowerup*>(map[line[i]]);
					WallBreakingPowerup* powerup = new WallBreakingPowerup(new S2D::Rect(original.SourceRect->X, original.SourceRect->Y, original.SourceRect->Width, original.SourceRect->Height),
						new S2D::Vector2(32 * i, 32 * lineNo), original.GetRenderDepth(), original.GetTextureKey());

					GameManager::GameObjectManager.AddGameObject(powerup);	
				}
			}
		}
		file.close();
	}
}

std::map<char, GameObject*> MapLoader::InitializeMap()
{
	std::map<char, GameObject*> map;
	map['B'] = new Block(new S2D::Rect(0, 0, 32, 32), new S2D::Vector2(0, 0), 2, false, "bigsquares");
	map['P'] = new Player(0.1f, new S2D::Rect(0, 0, 12, 16), new S2D::Vector2(0, 0), 3, "player2x");
	map['E'] = new Enemy(0.1f, new S2D::Rect(0, 0, 12*2, 16*2), new S2D::Vector2(0, 0), 3, "enemies");
	map['C'] = new Collectible(25, new S2D::Rect(0, 0, 24, 32), new S2D::Vector2(0, 0), 2, "collectible");
	map['D'] = new WallBreakingPowerup(new S2D::Rect(0, 0, 24, 32), new S2D::Vector2(0, 0), 2, "powerup");
	return map;
}