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
	/*private:
		std::shared_ptr<Player> player;*/
	};
}