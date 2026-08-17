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
#include "Export.h" 
#include "Logger.h"

namespace XYZEngine
{
	class ENGINE_API RangeAttackComponent : public Component
	{
	public:
		RangeAttackComponent(GameObject* gameObject);
		~RangeAttackComponent();

		void Update(float deltaTime) override;
		void Render() override;

		void SetAttackMode(bool autoAtt);
		void SetShouldAttack(bool should);
		void SetAttackCooldownTime(float speed);
		void SetAttackRadius(float radius);
		void SetDamage(int dmg);
		void SetTargets(std::vector<GameObject*> targets);
		float GetAttackCooldownTime();
		int GetAttackRadius();
		std::vector<GameObject*> FindTargets(float horizontalAxis, float verticalAxis);

	protected:
		std::vector<GameObject*> attackTargets;

	private:
		void CreateProjectile(Vector2Df direction);

		float attackCooldownTime = 0.f;
		float attackCooldown = 0.f;
		float attackRadius = 0.f;
		bool autoAttack = false;
		bool shouldAttack = false;
		int damage = 0;
	};
}
