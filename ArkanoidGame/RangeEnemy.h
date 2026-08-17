#pragma once
#include "Enemy.h"

namespace RoguelikeGame
{
	class RangeEnemy : public Enemy
	{
	public:
		RangeEnemy(const XYZEngine::Vector2Df& position, int textureMapIndex, XYZEngine::GameObject* player);
	};
}

