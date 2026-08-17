#include "DeveloperLevel.h"
#include <ResourceSystem.h>
#include <Engine.h>
#include <TransformComponent.h>
#include <FollowComponent.h>
#include "MazeGenerator.h"
#include "CreepSpawner.h"

using namespace XYZEngine;

namespace RoguelikeGame
{
	void DeveloperLevel::Start()
	{
		CreatBackground();
		player = std::make_unique<Player>(XYZEngine::Vector2Df{ 640.f, 360.f }, 0);
		CreepFactory factory;
		CreepSpawner spawner(&factory);
		spawner.SpawnCreeps(EnemyType::Melee, 5, player->GetPlayerGameObject(), floorCreated);
		spawner.SpawnCreeps(EnemyType::Range, 5, player->GetPlayerGameObject(), floorCreated);

		ResourceSystem::Instance()->LoadMusic("Sound", "Resources/Sounds/Sound.ogg");
		XYZEngine::Engine::Instance()->PlayMusic("Sound");
	}
	void DeveloperLevel::Restart()
	{
		Stop();
		Start();
	}
	void DeveloperLevel::Stop()
	{
		auto music = ResourceSystem::Instance()->GetMusicShared("Sound");
		if (music)
			music->stop();

		GameWorld::Instance()->Clear();
	}
	void DeveloperLevel::Update(float deltaTime)
	{
		if (!player->GetPlayerGameObject() || !player->GetPlayerGameObject()->IsAlive())
		{
			Restart();
			return;
		}
		player->Update(deltaTime);
	}
	void DeveloperLevel::CreatBackground()
	{
		ResourceSystem::Instance()->LoadTexture("Background", "Resources/Textures/Background.png");

		int width = 15;
		int height = 15;

		floorCreated.resize(height + 1, std::vector<bool>(width + 1, false));

		for (int y = 0; y < height + 1; y++)
		{
			for (int x = 0; x < width + 1; x++)
			{
				//if not wall place
				if (x != 0 && x != width && y != 0 && y != height)
				{
					floors.push_back(std::make_unique<Floor>(std::forward<XYZEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(0)));
					if (y < 16)
					{
						floorCreated[y][x] = true;
					}
				}

				//if left-bottom corner
				if (x == 0 && y == 0)
				{
					walls.push_back(std::make_unique<Wall>(std::forward<XYZEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(25)));
				}

				//if right-bottom corner
				if (x == width && y == 0)
				{
					walls.push_back(std::make_unique<Wall>(std::forward<XYZEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(27)));
				}

				//if left-top corner
				if (x == 0 && y == height)
				{
					walls.push_back(std::make_unique<Wall>(std::forward<XYZEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(1)));
				}

				//if right-top corner
				if (x == width && y == height)
				{
					walls.push_back(std::make_unique<Wall>(std::forward<XYZEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(3)));
				}

				//if left (not corner)
				if (x == 0 && y != height && y != 0)
				{
					floors.push_back(std::make_unique<Floor>(std::forward<XYZEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(18)));
					walls.push_back(std::make_unique<Wall>(std::forward<XYZEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(12)));
				}

				//if right (not corner)
				if (x == width && y != height && y != 0)
				{
					floors.push_back(std::make_unique<Floor>(std::forward<XYZEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(19)));
					walls.push_back(std::make_unique<Wall>(std::forward<XYZEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(12)));
				}

				//if bottom (not corner)
				if (y == 0 && x != width && x != 0)
				{
					walls.push_back(std::make_unique<Wall>(std::forward<XYZEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(38)));
				}

				//if top (not corner)
				if (y == height && x != width && x != 0)
				{
					walls.push_back(std::make_unique<Wall>(std::forward<XYZEngine::Vector2Df>({ x * 128.f, y * 128.f }), std::forward<int>(38)));
				}
			}
		}
		// Maze Generator
		MazeGenerator mazeGenerator(width, height, this);
		mazeGenerator.Generate();
	}
}