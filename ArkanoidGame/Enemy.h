#pragma once

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
	class Enemy : public XYZEngine::Component
	{

	public:
		Enemy(XYZEngine::GameObject* gameObject);

		void Update(float deltaTime) override;

		void Render() override {}

		int GetAttackRadius();

	private:
		int attackRadius = 70;
	};
}

