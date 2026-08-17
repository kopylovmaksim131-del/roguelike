#include "pch.h"
#include "AOEBossSpecial.h"

namespace XYZEngine
{
	AOEBossSpecial::AOEBossSpecial()
	{
		directions.push_back(Vector2Df{ 1, 0 });
		directions.push_back(Vector2Df{ 0, 1 });
		directions.push_back(Vector2Df{ -1, 0 });
		directions.push_back(Vector2Df{ 0, -1 });
		directions.push_back(Vector2Df{ 0.707, 0.707 });
		directions.push_back(Vector2Df{ -0.707, 0.707 });
		directions.push_back(Vector2Df{ -0.707, -0.707 });
		directions.push_back(Vector2Df{ 0.707, -0.707 });
	}

	float AOEBossSpecial::GetCooldown() const
	{
		return 3.0f;
	}

	void AOEBossSpecial::Execute(GameObject* boss, GameObject* target)
	{
		for (auto dir : directions)
		{
			auto myPos = boss->GetComponent<TransformComponent>()->GetWorldPosition();

			auto projectile = GameWorld::Instance()->CreateGameObject("Projectile");
			auto transform = projectile->GetComponent<TransformComponent>();
			transform->SetWorldPosition({ myPos.x + dir.x * 50.f, myPos.y + dir.y * 50.f });

			auto renderer = projectile->AddComponent<SpriteRendererComponent>();
			renderer->SetTexture(*ResourceSystem::Instance()->GetTextureShared("Bonus"));
			renderer->SetPixelSize(30, 30);

			auto body = projectile->AddComponent<RigidbodyComponent>();
			body->SetLinearVelocity(dir * 500.f);
			body->SetKinematic(false);

			auto collider = projectile->AddComponent<SpriteColliderComponent>();
			collider->SetTrigger(true);
			collider->SubscribeTriggerEnter([projectile](Trigger trigger) {
				auto otherObj = trigger.GetSecond()->GetGameObject();
				auto first = trigger.GetFirst()->GetGameObject();

				if (first->GetName() == "Player")
				{
					auto health = first->GetComponent<HealthComponent>();
					if (health)
						health->TakeDamage(10);
					GameWorld::Instance()->DestroyGameObject(projectile);
				}
				else if (otherObj->GetName() == "Wall")
				{
					GameWorld::Instance()->DestroyGameObject(projectile);
				}
				});
		}
	}
}