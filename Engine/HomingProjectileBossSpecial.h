#pragma once
#include "BossSpecial.h"
#include "TransformComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "ResourceSystem.h"
#include "SpriteColliderComponent.h"
#include "HealthComponent.h"
#include "FollowComponent.h"
#include "MeleeAttackComponent.h"
#include "LifetimeComponent.h"
#include "Export.h" 

namespace XYZEngine
{
	class ENGINE_API HomingProjectileBossSpecial : public BossSpecial
	{
	public:
		void Execute(GameObject* boss, GameObject* target) override;
		float GetCooldown() const override;
	};
}

