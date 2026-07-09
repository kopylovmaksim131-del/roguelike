#include "Background.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>

namespace RoguelikeGame
{
	Background::Background(XYZEngine::GameObject* gameObject) : XYZEngine::Component(gameObject)
	{
		auto backgroundRenderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		backgroundRenderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("Background"));
		backgroundRenderer->SetPixelSize(4000, 4000);
	}

	void Background::Update(float deltaTime)
	{
	}
}