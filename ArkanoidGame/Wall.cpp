#include "Wall.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>

namespace RoguelikeGame
{
	Wall::Wall(XYZEngine::GameObject* gameObject) : XYZEngine::Component(gameObject)
	{
		auto wallRenderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		wallRenderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("Wall"));

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();
		body->SetKinematic(true);

		gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();
	}

	void Wall::Update(float deltaTime)
	{
	}
}