#pragma once

#include <iostream>
#include <array>
#include "Scene.h"
#include "Player.h"
#include "Enemy.h"
#include "Background.h"
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
	private:
		void CreatPlayer();
		void CreatEnemy();
		void CreatBackground();
		void CreatWall(const std::string& name, float x, float y, int width, int height);
	};
}