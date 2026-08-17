#include "pch.h"
#include "BossSummonComponent.h"

namespace XYZEngine
{
	BossSummonComponent::BossSummonComponent(GameObject* gameObject) : Component(gameObject)
	{
	}

	BossSummonComponent::~BossSummonComponent()
	{
		for (auto target : attackTargets)
		{
			auto health = target->GetComponent<HealthComponent>();
			if (health)
			{
				health->UnsubscribeDeath([this, target]() {
					attackTargets.erase(
						std::remove(attackTargets.begin(), attackTargets.end(), target),
						attackTargets.end()
					);
					});
			}
		}
	}

	void BossSummonComponent::Update(float deltaTime)
	{
		auto phase = gameObject->GetComponent<BossPhaseComponent>();
		int countMultiplier = phase && phase->IsSecondPhase() ? 2 : 1;

		attackCooldown = std::min(attackCooldown + deltaTime, attackCooldownTime);

		if (autoAttack)
		{
			shouldAttack = true;
		}
		if (shouldAttack && attackCooldown >= attackCooldownTime)
		{
			LOG_INFO("MeleeAttackComponent::Update object name='" + gameObject->GetName() + "' attack'");

			for (auto target : attackTargets)
			{
				if (!target->IsAlive()) continue;

				auto targetPos = target->GetComponent<TransformComponent>()->GetWorldPosition();
				auto myPos = gameObject->GetComponent<TransformComponent>()->GetWorldPosition();

				Vector2Df direction = { targetPos.x - myPos.x, targetPos.y - myPos.y };

				float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
				if (length > 0)
				{
					direction.x /= length;
					direction.y /= length;
				}

				Vector2Df position = CheckPosition({ myPos.x + direction.x * 100.f, myPos.y + direction.y * 100.f });

				CreateCommonEnemy(target, position, countMultiplier);
			}

			attackTargets.erase(
				std::remove_if(attackTargets.begin(), attackTargets.end(),
					[](GameObject* target) { return !target->IsAlive(); }),
				attackTargets.end()
			);

			attackCooldown = 0.f;
			shouldAttack = false;
		}
	}

	void BossSummonComponent::Render()
	{
	}

	void BossSummonComponent::SetEnemyCount(int enemyCount)
	{
		this->enemyCount = enemyCount;
	}

	void BossSummonComponent::SetAttackMode(bool autoAtt)
	{
		autoAttack = autoAtt;
	}

	void BossSummonComponent::SetShouldAttack(bool should)
	{
		shouldAttack = should;
	}

	void BossSummonComponent::SetAttackCooldownTime(float cooldown)
	{
		attackCooldownTime = cooldown;
	}

	void BossSummonComponent::SetAttackRadius(float radius)
	{
		attackRadius = radius;
	}

	float BossSummonComponent::GetAttackCooldownTime()
	{
		return attackCooldownTime;
	}

	int BossSummonComponent::GetAttackRadius()
	{
		return attackRadius;
	}

	void BossSummonComponent::SetTargets(std::vector<GameObject*> targets)
	{
		for (auto oldTarget : attackTargets)
		{
			auto health = oldTarget->GetComponent<HealthComponent>();
			if (health)
			{
				health->UnsubscribeDeath([this, oldTarget]() {
					attackTargets.erase(
						std::remove(attackTargets.begin(), attackTargets.end(), oldTarget),
						attackTargets.end()
					);
					});
			}
		}

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

	void BossSummonComponent::CreateCommonEnemy(GameObject* target, Vector2Df position, int countMultiplier)
	{
		int newEnemycount = enemyCount * countMultiplier;
		for (int i = 0; i < newEnemycount; i++)
		{
			auto creep = GameWorld::Instance()->CreateGameObject("Enemy");

			auto follow = creep->AddComponent<FollowComponent>();
			follow->SetFollowTarget(target);
			follow->SetRadius(1000.f);
			follow->SetSpeed(200.f);

			auto renderer = creep->AddComponent<SpriteRendererComponent>();
			renderer->SetTexture(*ResourceSystem::Instance()->GetTextureShared("Bonus"));
			renderer->SetPixelSize(50, 50);

			creep->GetComponent<TransformComponent>()->SetWorldPosition(position);

			creep->AddComponent<RigidbodyComponent>();
			creep->AddComponent<SpriteColliderComponent>();
			creep->AddComponent<HealthComponent>();
			creep->AddComponent<ArmorComponent>();

			if (isMelee)
			{
				CreateMeleeEnemy(creep, target);
				isMelee = false;
			}
			else
			{
				CreateRangeEnemy(creep, target);
				isMelee = true;
			}
		}
	}

	void BossSummonComponent::CreateMeleeEnemy(GameObject* creep, GameObject* target)
	{
		auto hp = creep->GetComponent<HealthComponent>();
		hp->SetHP(1);
		hp->SetMaxHP(70);

		auto armor = creep->GetComponent<ArmorComponent>();
		armor->SetArmore(1);

		auto attack = creep->AddComponent<MeleeAttackComponent>();
		attack->SetTargets(std::vector< GameObject*> { target });
		attack->SetAttackMode(true);
		attack->SetAttackRadius(150.f);
		attack->SetAttackCooldownTime(1.5f);
		attack->SetDamage(10);
	}

	void BossSummonComponent::CreateRangeEnemy(GameObject* creep, GameObject* target)
	{
		auto hp = creep->GetComponent<HealthComponent>();
		hp->SetHP(40);
		hp->SetMaxHP(40);

		auto armor = creep->GetComponent<ArmorComponent>();
		armor->SetArmore(5);

		auto attack = creep->AddComponent<RangeAttackComponent>();
		attack->SetTargets(std::vector<GameObject*> { target });
		attack->SetAttackMode(true);
		attack->SetAttackRadius(550.f);
		attack->SetAttackCooldownTime(1.5f);
		attack->SetDamage(6);
	}

	Vector2Df BossSummonComponent::CheckPosition(Vector2Df position)
	{
		auto myPos = gameObject->GetComponent<TransformComponent>()->GetWorldPosition();
		auto gameObjects = GameWorld::Instance()->GetGameObjects();

		for (int attempt = 0; attempt < 20; attempt++)
		{
			float angle = (std::rand() % 360) * 3.14159f / 180.f;
			float radius = 150.f + (std::rand() % 100);

			Vector2Df candidate = {
				myPos.x + std::cos(angle) * radius,
				myPos.y + std::sin(angle) * radius
			};

			bool occupied = false;
			for (auto obj : gameObjects)
			{
				if (obj == gameObject) continue;
				auto objPos = obj->GetComponent<TransformComponent>()->GetWorldPosition();
				float dx = candidate.x - objPos.x;
				float dy = candidate.y - objPos.y;
				if (std::sqrt(dx * dx + dy * dy) < 64.f)
				{
					occupied = true;
					break;
				}
			}

			if (!occupied)
				return candidate;
		}

		return position;
	}
}