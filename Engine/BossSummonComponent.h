#pragma once
#include "Component.h"
#include "GameWorld.h"
#include "TransformComponent.h"
#include "ArmorComponent.h"
#include "HealthComponent.h"
#include "SpriteRendererComponent.h"
#include "ResourceSystem.h"
#include "SpriteColliderComponent.h"
#include "ColliderComponent.h"
#include "FollowComponent.h"
#include "MeleeAttackComponent.h"
#include "RangeAttackComponent.h"
#include "BossPhaseComponent.h"
#include "Trigger.h"
#include "Export.h" 
#include "Logger.h"

namespace XYZEngine
{
	class ENGINE_API BossSummonComponent : public Component
	{
	public:
		BossSummonComponent(GameObject* gameObject);
		~BossSummonComponent();

		void Update(float deltaTime) override;
		void Render() override;

		void SetEnemyCount(int enemyCount);
		void SetAttackMode(bool autoAtt);
		void SetShouldAttack(bool should);
		void SetAttackCooldownTime(float speed);
		void SetAttackRadius(float radius);
		void SetDamage(int dmg);
		void SetTargets(std::vector<GameObject*> targets);
		float GetAttackCooldownTime();
		int GetAttackRadius();

	protected:
		std::vector<GameObject*> attackTargets;

	private:
		void CreateCommonEnemy(GameObject* target, Vector2Df position, int countMultiplier);
		void CreateMeleeEnemy(GameObject* enemy, GameObject* target);
		void CreateRangeEnemy(GameObject* enemy, GameObject* target);
		Vector2Df CheckPosition(Vector2Df position);

		bool isMelee = true;
		int enemyCount = 0;

		float attackCooldownTime = 0.f;
		float attackCooldown = 0.f;
		float attackRadius = 0.f;
		bool autoAttack = false;
		bool shouldAttack = false;
	};
}
