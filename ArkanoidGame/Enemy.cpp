#include "Enemy.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>

namespace RoguelikeGame
{
	Enemy::Enemy(const XYZEngine::Vector2Df& position, int textureMapIndex, XYZEngine::GameObject* player)
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Enemy");

		auto follow = gameObject->AddComponent<XYZEngine::FollowComponent>();
		follow->SetFollowTarget(player);
		follow->SetRadius(1000.f);
		follow->SetSpeed(200.f);

		auto renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("Bonus"));
		renderer->SetPixelSize(100, 100);

		gameObject->GetComponent<XYZEngine::TransformComponent>()->SetWorldPosition(position);

		gameObject->AddComponent<XYZEngine::RigidbodyComponent>();
		gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();
		gameObject->AddComponent<XYZEngine::HealthComponent>();
		gameObject->AddComponent<XYZEngine::ArmorComponent>();
	}
}