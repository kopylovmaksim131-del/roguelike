#pragma once

#include <iostream>
#include <array>
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Floor.h"
#include "Wall.h"

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

		std::vector<std::unique_ptr<Wall>> walls;
		std::vector<std::unique_ptr<Floor>> floors;
		std::vector<std::vector<bool>> floorCreated;

	private:
		std::unique_ptr<Player> player;
		void CreatBackground();
	};
}