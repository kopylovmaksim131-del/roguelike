#pragma once

#include "CameraComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "InputComponent.h"
#include "HealthComponent.h"
#include "ArmorComponent.h"
#include "MeleeAttackComponent.h"
#include "GameObject.h"

namespace RoguelikeGame
{
	class Player : public XYZEngine::Component
	{

	public:
		Player(XYZEngine::GameObject* gameObject);

		void Update(float deltaTime) override;

		void Render() override {}
	private:
		float lastHorizontalAxis = 0.f;
		float lasVerticalAxis = 0.f;
	};
}

