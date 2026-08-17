#include "pch.h"
#include "AnimationComponent.h"

namespace XYZEngine
{
	AnimationComponent::AnimationComponent(GameObject* gameObject) : Component(gameObject)
	{
	}
	AnimationComponent::~AnimationComponent()
	{
	}
	void AnimationComponent::Update(float deltaTime)
	{
		animationTimer += deltaTime;
		if (animationTimer >= frameDuration)
		{
			animationTimer = 0.f;
			currentFrame = (currentFrame + 1) % totalFrames;

			auto renderer = gameObject->GetComponent<XYZEngine::SpriteRendererComponent>();
			if (renderer)
			{
				renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureMapElementShared(textureName, currentFrame));
			}
		}
	}
	void AnimationComponent::Render()
	{
	}
	void AnimationComponent::SetAnimation(std::string textureName, float frameDuration, int totalFrames, int currentFrame)
	{
		this->frameDuration = frameDuration;
		this->totalFrames = totalFrames;
		this->currentFrame = currentFrame;
		this->textureName = textureName;
	}
}