#include "pch.h"
#include "DirectionalVolleyBossSpecial.h"

namespace XYZEngine
{
	float DirectionalVolleyBossSpecial::GetCooldown() const
	{
		return 3.0f;
	}

	void DirectionalVolleyBossSpecial::Execute(GameObject* boss, GameObject* target)
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

		Vector2Df perp = { -direction.y, direction.x };

		float spreadAngle = 0.15f;
		float startOffset = -(projectileCount - 1) * spreadAngle / 2.f;

		for (int i = 0; i < projectileCount; i++)
		{
			float offset = startOffset + i * spreadAngle;
			Vector2Df newDirection = {
				direction.x + perp.x * offset,
				direction.y + perp.y * offset
			};

			float len = std::sqrt(newDirection.x * newDirection.x + newDirection.y * newDirection.y);
			newDirection.x /= len;
			newDirection.y /= len;

			auto projectile = GameWorld::Instance()->CreateGameObject("Projectile");
			auto transform = projectile->GetComponent<TransformComponent>();
			transform->SetWorldPosition({ myPos.x + newDirection.x * 50.f, myPos.y + newDirection.y * 50.f });

			auto renderer = projectile->AddComponent<SpriteRendererComponent>();
			renderer->SetTexture(*ResourceSystem::Instance()->GetTextureShared("Bonus"));
			renderer->SetPixelSize(30, 30);

			auto body = projectile->AddComponent<RigidbodyComponent>();
			body->SetLinearVelocity(newDirection * 500.f);
			body->SetKinematic(false);

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
}
