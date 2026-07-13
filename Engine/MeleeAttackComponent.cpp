#include "pch.h"
#include "MeleeAttackComponent.h"
#include "assert.h"

namespace XYZEngine
{
	MeleeAttackComponent::MeleeAttackComponent(GameObject* gameObject) : Component(gameObject)
	{
	}
	MeleeAttackComponent::~MeleeAttackComponent()
	{
	}
	void MeleeAttackComponent::Update(float deltaTime)
	{
		attackCooldown = std::min(attackCooldown + deltaTime, attackCooldownTime);

		if (autoAttack)
		{
			shouldAttack = true;
		}
		if (shouldAttack && attackCooldown >= attackCooldownTime)
		{
			auto name = gameObject->GetName();
			LOG_INFO("MeleeAttackComponent::Update object name='" + name + "' attack'");

			for (auto target : attackTargets)
			{
				auto targetPos = target->GetComponent<TransformComponent>()->GetWorldPosition();
				auto myPos = gameObject->GetComponent<TransformComponent>()->GetWorldPosition();

				Vector2Df direction = { targetPos.x - myPos.x, targetPos.y - myPos.y };

				float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

				if (length <= attackRadius)
				{
					if (target->GetComponent<ArmorComponent>())
					{
						target->GetComponent<HealthComponent>()->TakeDamage(target->GetComponent<ArmorComponent>()->TakeDamage(damage));
					}
					else
					{
						target->GetComponent<HealthComponent>()->TakeDamage(damage);
					}

				}
			}
			attackCooldown = 0.f;
			shouldAttack = false;
		}
	}
	void MeleeAttackComponent::Render()
	{
	}
	void MeleeAttackComponent::SetAttackMode(bool autoAtt)
	{
		autoAttack = autoAtt;
	}
	void MeleeAttackComponent::SetShouldAttack(bool should)
	{
		shouldAttack = should;
	}
	void MeleeAttackComponent::SetAttackCooldownTime(float cooldown)
	{
		assert(cooldown > 0 && "Cooldown must be positive");
		LOG_WARN("MeleeAttackComponent::SetAttackCooldownTime object cooldown='" + std::to_string(cooldown));
		attackCooldownTime = cooldown;
	}
	void MeleeAttackComponent::SetAttackRadius(float radius)
	{
		attackRadius = radius;
	}
	void MeleeAttackComponent::SetDamage(int dmg)
	{
		damage = dmg;
	}
	void MeleeAttackComponent::SetTargets(std::vector<GameObject*> targets)
	{
		attackTargets = targets;
		for (auto target : attackTargets)
		{
			auto health = target->GetComponent<HealthComponent>();
			if (health)
			{
				health->SubscribeDeath([this, target]() {
					attackTargets.erase(
						std::remove(attackTargets.begin(), attackTargets.end(), target),
						attackTargets.end()
					);
					});
			}
		}
	}
	float MeleeAttackComponent::GetAttackCooldownTime()
	{
		return attackCooldownTime;
	}
	int MeleeAttackComponent::GetAttackRadius()
	{
		return attackRadius;
	}
	std::vector<GameObject*> MeleeAttackComponent::FindTargets(float horizontalAxis, float verticalAxis)
	{
		std::vector<GameObject*> targets;

		float attackLen = std::sqrt(horizontalAxis * horizontalAxis + verticalAxis * verticalAxis);
		if (attackLen == 0)
		{
			return targets;
		}
		Vector2Df attackDir = { horizontalAxis / attackLen, verticalAxis / attackLen };

		auto gameObjects = GameWorld::Instance()->GetGameObjects();
		auto myPos = gameObject->GetComponent<TransformComponent>()->GetWorldPosition();

		for (auto target : gameObjects)
		{
			if (target->GetComponent<HealthComponent>() == nullptr || target == gameObject)
			{
				continue;
			}

			auto targetPos = target->GetComponent<TransformComponent>()->GetWorldPosition();
			Vector2Df toEnemy = { targetPos.x - myPos.x, targetPos.y - myPos.y };

			float toEnemyLen = std::sqrt(toEnemy.x * toEnemy.x + toEnemy.y * toEnemy.y);
			if (toEnemyLen == 0)
			{
				continue;
			}

			Vector2Df toEnemyDir = { toEnemy.x / toEnemyLen, toEnemy.y / toEnemyLen };
			float dot = attackDir.x * toEnemyDir.x + attackDir.y * toEnemyDir.y;

			if (dot >= 0.7f && toEnemyLen <= attackRadius)
			{
				targets.push_back(target);
			}
		}

		return targets;
	}
}