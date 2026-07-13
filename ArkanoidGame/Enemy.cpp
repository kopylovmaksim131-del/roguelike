#include "Enemy.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>

namespace RoguelikeGame
{
	Enemy::Enemy(XYZEngine::GameObject* gameObject) : XYZEngine::Component(gameObject)
	{
		auto enemyRenderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		enemyRenderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("Bonus"));
		enemyRenderer->SetPixelSize(32, 32);

		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		transform->SetWorldPosition( 640.f, 100.f );

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();

		auto hp = gameObject->AddComponent<XYZEngine::HealthComponent>();
		hp->SetHP(70);
		hp->SetMaxHP(70);

		auto armore = gameObject->AddComponent<XYZEngine::ArmorComponent>();
		armore->SetArmore(10);
		armore->SetMaxArmore(40);

		auto attack = gameObject->AddComponent<XYZEngine::MeleeAttackComponent>();
		attack->SetAttackRadius(50.f);
		attack->SetAttackCooldownTime(1.5f);
		attack->SetDamage(10);
		attack->SetAttackMode(true);
	}

	void Enemy::Update(float deltaTime)
	{
	}
	int Enemy::GetAttackRadius()
	{
		return attackRadius;
	}
}