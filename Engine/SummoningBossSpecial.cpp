#include "pch.h"
#include "SummoningBossSpecial.h"

namespace XYZEngine
{
	SummoningBossSpecial::SummoningBossSpecial()
	{
	}

	float SummoningBossSpecial::GetCooldown() const
	{
		return 3.0f;
	}

	void SummoningBossSpecial::Execute(GameObject* boss, GameObject* target)
	{
		auto targetPos = target->GetComponent<TransformComponent>()->GetWorldPosition();
		auto myPos = boss->GetComponent<TransformComponent>()->GetWorldPosition();

		Vector2Df direction = { targetPos.x - myPos.x, targetPos.y - myPos.y };

		float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		if (length > 0)
		{
			direction.x /= length;
			direction.y /= length;
		}
	}

	void SummoningBossSpecial::CreateCommonEnemy(GameObject* target, Vector2Df position)
	{
		auto gameObject = GameWorld::Instance()->CreateGameObject("Enemy");

		auto follow = gameObject->AddComponent<FollowComponent>();
		follow->SetFollowTarget(target);
		follow->SetRadius(1000.f);
		follow->SetSpeed(200.f);

		auto renderer = gameObject->AddComponent<SpriteRendererComponent>();
		renderer->SetTexture(*ResourceSystem::Instance()->GetTextureShared("Bonus"));
		renderer->SetPixelSize(100, 100);

		gameObject->GetComponent<TransformComponent>()->SetWorldPosition(position);

		gameObject->AddComponent<RigidbodyComponent>();
		gameObject->AddComponent<SpriteColliderComponent>();
		gameObject->AddComponent<HealthComponent>();
		gameObject->AddComponent<ArmorComponent>();

		for (int i = 0; i < enemyCount; i++)
		{
			if (isMelee)
			{
				CreateMeleeEnemy(gameObject, target);
				isMelee = false;
			}
			else
			{
				CreateRangeEnemy(gameObject, target);
				isMelee = true;
			}
		}
	}

	void SummoningBossSpecial::CreateMeleeEnemy(GameObject* gameObject, GameObject* target)
	{
		auto hp = gameObject->GetComponent<HealthComponent>();
		hp->SetHP(1);
		hp->SetMaxHP(70);

		auto armor = gameObject->GetComponent<ArmorComponent>();
		armor->SetArmore(1);

		auto attack = gameObject->AddComponent<MeleeAttackComponent>();
		attack->SetTargets(std::vector<GameObject*> { target });
		attack->SetAttackMode(true);
		attack->SetAttackRadius(150.f);
		attack->SetAttackCooldownTime(1.5f);
		attack->SetDamage(10);
	}

	void SummoningBossSpecial::CreateRangeEnemy(GameObject* gameObject, GameObject* target)
	{
		auto hp = gameObject->GetComponent<HealthComponent>();
		hp->SetHP(40);
		hp->SetMaxHP(40);

		auto armor = gameObject->GetComponent<ArmorComponent>();
		armor->SetArmore(5);

		auto attack = gameObject->AddComponent<RangeAttackComponent>();
		attack->SetTargets(std::vector<GameObject*> { target });
		attack->SetAttackMode(true);
		attack->SetAttackRadius(550.f);
		attack->SetAttackCooldownTime(1.5f);
		attack->SetDamage(6);
	}
}