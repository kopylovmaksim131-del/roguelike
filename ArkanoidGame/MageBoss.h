#pragma once
#include "Enemy.h"
#include "BossRangeAttackComponent.h"
#include "AOEBossSpecial.h"
#include "BossPhaseComponent.h"
#include "HomingProjectileBossSpecial.h"
#include "DirectionalVolleyBossSpecial.h"

namespace RoguelikeGame
{
	class MageBoss : public Enemy
	{
	public:
		MageBoss(const XYZEngine::Vector2Df& position, int textureMapIndex, XYZEngine::GameObject* player);
	};
}
