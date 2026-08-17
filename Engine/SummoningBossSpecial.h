#pragma once
#include "BossSpecial.h"
#include "TransformComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "ResourceSystem.h"
#include "SpriteColliderComponent.h"
#include "HealthComponent.h"
#include "Export.h" 
#include "FollowComponent.h"
#include "ArmorComponent.h"
#include "RangeAttackComponent.h"

namespace XYZEngine
{
	class ENGINE_API SummoningBossSpecial : public BossSpecial
	{
	public:
		SummoningBossSpecial();
		void Execute(GameObject* boss, GameObject* target) override;
		float GetCooldown() const override;

	private:
		void CreateCommonEnemy(GameObject* target, Vector2Df position);
		void CreateMeleeEnemy(GameObject* enemy, GameObject* target);
		void CreateRangeEnemy(GameObject* enemy, GameObject* target);

		bool isMelee = true;
		int enemyCount = 0;
	};
}

