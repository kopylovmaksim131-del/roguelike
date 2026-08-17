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
		exitActive = false;
		isTransitioning = false;
		fadeTimer = 2.f;
		faderIsActive = false;
		this->SetFinished(false);
		isBossLevel = !isBossLevel;

		CreatBackground();

		std::vector<std::pair<int, int>> freeCells = GetFreeCells();

		LootFactory lootFactoryHealin(LootType::HealingPotion, 3, freeCells, "HealingPotion");
		LootFactory lootFactoryArmore(LootType::ArmorePotion, 2, freeCells, "ArmorPotion");
		

		XYZEngine::Vector2Df exitPos = GetRandomFreeCells(freeCells);
		exit = std::make_unique<LevelExit>(XYZEngine::Vector2Df{ exitPos.x, exitPos.y }, 16);

		XYZEngine::Vector2Df playerPos = GetRandomFreeCells(freeCells);
		Player::Instance()->Init(playerPos, 0);
		CreepFactory factory;
		CreepSpawner spawner(&factory);

		if (isBossLevel)
		{
			LootFactory lootFactoryStrength(LootType::StrengthPotion, 1, freeCells, "StrengthPotion");
			LootFactory lootFactorySpeed(LootType::SpeedPotion, 1, freeCells, "SpeedPotion");

			EnemyType bossType = (std::rand() % 2 == 0) ? EnemyType::Mage : EnemyType::Summoner;
			spawner.SpawnCreeps(bossType, 1, Player::Instance()->GetPlayerGameObject(), freeCells);
			ResourceSystem::Instance()->LoadMusic("BossSound", "Resources/Sounds/bossFight1.wav");
			XYZEngine::Engine::Instance()->PlayMusic("BossSound");
			soundName = "BossSound";
		}
		else
		{
			int enemyCount = 1 + std::rand() % 6;
			spawner.SpawnCreeps(EnemyType::Melee, enemyCount, Player::Instance()->GetPlayerGameObject(), freeCells);
			spawner.SpawnCreeps(EnemyType::Range, enemyCount, Player::Instance()->GetPlayerGameObject(), freeCells);
			ResourceSystem::Instance()->LoadMusic("Sound", "Resources/Sounds/Sound.ogg");
			XYZEngine::Engine::Instance()->PlayMusic("Sound");
			soundName = "Sound";
		}
	}

	void DeveloperLevel::Restart()
	{
		Stop();
		Start();
	}

	void DeveloperLevel::Stop()
	{
		auto music = ResourceSystem::Instance()->GetMusicShared(soundName);
		if (music)
			music->stop();

		GameWorld::Instance()->Clear();
	}

	void DeveloperLevel::Update(float deltaTime)
	{
		if (!Player::Instance()->GetPlayerGameObject() || !Player::Instance()->GetPlayerGameObject()->IsAlive())
		{
			isBossLevel = true;
			Restart();
			return;
		}
		Player::Instance()->Update(deltaTime);

		if (CountEnemies() == 1 && !exitActive)
			ActivateExit();

		if (isTransitioning && !faderIsActive)
			StartTransition();

		if (faderIsActive && fadeTimer > 0.f)
		{
			UpdateFader(deltaTime);
			MovePlayerToExit(deltaTime);
		}

		if (fadeTimer <= 0.f)
			this->SetFinished(true);
	}

	int DeveloperLevel::CountEnemies()
	{
		std::vector<XYZEngine::GameObject*> objects = XYZEngine::GameWorld::Instance()->GetGameObjects();

		int enemyCount = 0;
		for (auto obj : objects)
		{
			if (obj->GetComponent<XYZEngine::HealthComponent>())
			{
				enemyCount++;
			}
		}

		return enemyCount;
	}

	void DeveloperLevel::ActivateExit()
	{
		exitActive = true;
		auto gameObject = exit->GetGameObject();

		auto renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureMapElementShared("level_floors", 16));
		renderer->SetPixelSize(128, 128);

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();
		collider->SetTrigger(true);
		collider->SubscribeTriggerEnter([this](XYZEngine::Trigger trigger) {
			this->SetIsTransitioning();
			});

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();
		body->SetKinematic(false);
	}

	void DeveloperLevel::StartTransition()
	{
		faderIsActive = true;

		auto playerObj = Player::Instance()->GetPlayerGameObject();

		auto gameObject = GameWorld::Instance()->CreateGameObject("Fader");

		playerObj->RemoveComponent(playerObj->GetComponent<XYZEngine::InputComponent>());

		playerObj->GetComponent<RigidbodyComponent>()->SetLinearVelocity({ 0.f, 0.f });

		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		transform->SetWorldPosition(playerObj->GetComponent<TransformComponent>()->GetWorldPosition());

		auto renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("Fader"));
		renderer->SetPixelSize(2000, 2000);
		renderer->setAlfaSpriteColor(0);
	}

	void DeveloperLevel::UpdateFader(float deltaTime)
	{
		float alfa = (fadeDuration - fadeTimer) / fadeDuration;
		auto gameObj = GameWorld::Instance()->GetGameObjectByName("Fader");
		if (gameObj)
			gameObj->GetComponent<SpriteRendererComponent>()->setAlfaSpriteColor(255 * alfa);

		fadeTimer -= deltaTime;
	}

	void DeveloperLevel::MovePlayerToExit(float deltaTime)
	{
		auto playerPos = Player::Instance()->GetPlayerGameObject()->GetComponent<TransformComponent>()->GetWorldPosition();
		auto exitPos = exit->GetGameObject()->GetComponent<TransformComponent>()->GetWorldPosition();

		float dx = exitPos.x - playerPos.x;
		float dy = exitPos.y - playerPos.y;
		float length = std::sqrt(dx * dx + dy * dy);

		if (length > 2.f)
		{
			float step = 150.f * deltaTime;
			if (step > length)
				step = length;
			Player::Instance()->GetPlayerGameObject()->GetComponent<TransformComponent>()->MoveBy({ dx / length * step, dy / length * step });
		}
	}

	void DeveloperLevel::SetIsTransitioning()
	{
		isTransitioning = true;
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
		if (!isBossLevel)
		{
			MazeGenerator mazeGenerator(width, height, this);
			mazeGenerator.Generate();
		}
	}

	std::vector<std::pair<int, int>> DeveloperLevel::GetFreeCells()
	{
		std::vector<std::pair<int, int>> freeCells;
		for (int y = 0; y < floorCreated.size(); ++y)
		{
			for (int x = 0; x < floorCreated[y].size(); ++x)
			{
				if (floorCreated[y][x])
				{
					freeCells.push_back({ x, y });
				}
			}
		}

		return freeCells;
	}

	XYZEngine::Vector2Df DeveloperLevel::GetRandomFreeCells(std::vector<std::pair<int, int>>& freeCells)
	{
		int index = std::rand() % freeCells.size();
		std::pair<int, int> cell = freeCells[index];
		int x = cell.first;
		int y = cell.second;
		if (index < freeCells.size())
		{
			freeCells.erase(freeCells.begin() + index);
		}
		XYZEngine::Vector2Df position{ x * 128.f, y * 128.f };

		return position;
	}
}