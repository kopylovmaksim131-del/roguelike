#pragma once
#include "BossSpecial.h"
#include "TransformComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "ResourceSystem.h"
#include "SpriteColliderComponent.h"
#include "HealthComponent.h"
#include "Export.h" 

namespace XYZEngine
{
	class ENGINE_API AOEBossSpecial : public BossSpecial
	{
	public:
		AOEBossSpecial();
		void Execute(GameObject* boss, GameObject* target) override;
		float GetCooldown() const override;

	private:
		std::vector<Vector2Df> directions;
	};
}

