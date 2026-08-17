#pragma once
#include "Component.h"
#include "TransformComponent.h"
#include "ArmorComponent.h"
#include "HealthComponent.h"
#include "SpriteRendererComponent.h"
#include "ResourceSystem.h"
#include "SpriteColliderComponent.h"
#include "ColliderComponent.h"
#include "Trigger.h"
#include "RangeAttackComponent.h"
#include "Export.h" 
#include "BossSpecial.h"
#include "BossPhaseComponent.h"
#include "Logger.h"

namespace XYZEngine
{
	class ENGINE_API BossRangeAttackComponent : public RangeAttackComponent
	{
	public:
		BossRangeAttackComponent(GameObject* gameObject) : RangeAttackComponent(gameObject) {}

		void AddSpecial(std::shared_ptr<BossSpecial> special);
		void Update(float deltaTime) override;

	private:
		std::vector<std::shared_ptr<BossSpecial>> specials;
		int currentSpecial = 0;
		float specialTimer = 0.f;
	};
}
