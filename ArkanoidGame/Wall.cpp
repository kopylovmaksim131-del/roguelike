#include "Wall.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>

RoguelikeGame::Wall::Wall(const XYZEngine::Vector2Df position, int textureMapIndex)
{
	gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Wall");
	auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
	transform->SetWorldPosition(position);

	auto renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();

	auto tex = XYZEngine::ResourceSystem::Instance()->GetTextureMapElementShared("level_walls", textureMapIndex);
	if (!tex) {
		std::cerr << "TextureMapElement is NULL for index " << textureMapIndex << std::endl;
		return;
	}
	renderer->SetTexture(*tex);

	//renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureMapElementShared("level_walls", textureMapIndex));
	//renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("Wall"));
	renderer->SetPixelSize(128, 128);

	auto rigidbody = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();
	rigidbody->SetKinematic(true);

	auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();
}