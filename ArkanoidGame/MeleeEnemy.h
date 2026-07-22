#pragma once
#include "Enemy.h"

namespace RoguelikeGame
{
	class MeleeEnemy : public Enemy
	{
	public:
		MeleeEnemy(const XYZEngine::Vector2Df& position, int textureMapIndex, XYZEngine::GameObject* player);
	};
}
