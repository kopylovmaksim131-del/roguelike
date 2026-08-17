#include "pch.h"
#include "HomingProjectileBossSpecial.h"

namespace XYZEngine
{
	float HomingProjectileBossSpecial::GetCooldown() const
	{
		return 3.0f;
	}

	void HomingProjectileBossSpecial::Execute(GameObject* boss, GameObject* target)
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

		auto projectile = GameWorld::Instance()->CreateGameObject("Projectile");
		auto transform = projectile->GetComponent<TransformComponent>();
		transform->SetWorldPosition({ myPos.x + direction.x * 50.f, myPos.y + direction.y * 50.f });

		auto renderer = projectile->AddComponent<SpriteRendererComponent>();
		renderer->SetTexture(*ResourceSystem::Instance()->GetTextureShared("Bonus"));
		renderer->SetPixelSize(30, 30);

		auto body = projectile->AddComponent<RigidbodyComponent>();
		//body->SetLinearVelocity(direction * 200.f);
		body->SetKinematic(false);

		auto follow = projectile->AddComponent<FollowComponent>();
		follow->SetFollowTarget(target);
		follow->SetRadius(20000);
		follow->SetSpeed(200.f);

		auto attack = projectile->AddComponent<MeleeAttackComponent>();
		attack->SetTargets(std::vector<GameObject*> { target });
		attack->SetAttackMode(false);
		attack->SetAttackRadius(5.f);
		attack->SetAttackCooldownTime(1.f);
		attack->SetDamage(1);

		auto lifeTime = projectile->AddComponent<LifetimeComponent>();

		auto collider = projectile->AddComponent<SpriteColliderComponent>();
		collider->SetTrigger(true);
		collider->SubscribeTriggerEnter([projectile](Trigger trigger) {
			auto otherObj = trigger.GetSecond()->GetGameObject();
			auto first = trigger.GetFirst()->GetGameObject();

			if (first->GetName() == "Player" || otherObj->GetName() == "Player")
			{
				auto health = first->GetComponent<HealthComponent>();
				if (health)
					health->TakeDamage(10);
				GameWorld::Instance()->DestroyGameObject(projectile);
			}
			else if (first->GetName() == "Wall" || otherObj->GetName() == "Wall")
			{
				GameWorld::Instance()->DestroyGameObject(projectile);
			}
			});
	}
}