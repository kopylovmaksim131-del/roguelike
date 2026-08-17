#pragma once
#include "Enemy.h"
#include "BossPhaseComponent.h"
#include "SummoningBossSpecial.h"
#include "BossRangeAttackComponent.h"
#include "BossSummonComponent.h"

namespace RoguelikeGame
{
	class SummonBoss : public Enemy
	{
	public:
		SummonBoss(const XYZEngine::Vector2Df& position, int textureMapIndex, XYZEngine::GameObject* player);
	};
}
