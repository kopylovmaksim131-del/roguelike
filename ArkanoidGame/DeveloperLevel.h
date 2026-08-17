#pragma once

#include <iostream>
#include <array>
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Floor.h"
#include "Wall.h"
#include "LevelExit.h"
#include "Loot.h"
#include "Logger.h"
#include "LootFactory.h"

using namespace XYZEngine;

namespace RoguelikeGame
{
	class DeveloperLevel : public Scene
	{
	public:
		void Start() override;
		void Restart() override;
		void Stop() override;
		void Update(float deltaTime) override;

		void SetIsTransitioning();

		std::vector<std::unique_ptr<Wall>> walls;
		std::vector<std::unique_ptr<Floor>> floors;
		std::vector<std::vector<bool>> floorCreated;

	private:
		int CountEnemies();
		void ActivateExit();
		void StartTransition();
		void UpdateFader(float deltaTime);
		void MovePlayerToExit(float deltaTime);

		std::unique_ptr<LevelExit> exit;
		bool exitActive = false;
		bool isTransitioning = false;
		void CreatBackground();
		std::vector<std::pair<int, int>> GetFreeCells();
		XYZEngine::Vector2Df GetRandomFreeCells(std::vector<std::pair<int, int>>& freeCells);
		float fadeTimer = 2.f;
		float fadeDuration = 2.f;
		bool faderIsActive = false;
		bool isBossLevel = true;
		std::string soundName;
	};
}