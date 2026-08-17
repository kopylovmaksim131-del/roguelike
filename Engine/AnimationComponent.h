#pragma once
#include "Component.h"
#include "SpriteRendererComponent.h"
#include "ResourceSystem.h"

namespace XYZEngine
{
	class ENGINE_API AnimationComponent : public Component
	{
	public:
		AnimationComponent(GameObject* gameObject);
		~AnimationComponent();

		void Update(float deltaTime) override;
		void Render() override;
		void SetAnimation(std::string textureName, float frameDuration, int totalFrames, int currentFrame = 0);

	private:
		float animationTimer = 0.f;
		float frameDuration = 0.f;
		int currentFrame = 0;
		int totalFrames = 0;
		std::string textureName;
	};
}
