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
	}

	void Enemy::Update(float deltaTime)
	{
	}
}