#pragma once

#include "CameraComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "InputComponent.h"
#include "GameObject.h"

namespace RoguelikeGame
{
	class Player : public XYZEngine::Component
	{

	public:
		Player(XYZEngine::GameObject* gameObject);

		void Update(float deltaTime) override;

		void Render() override {}

	};
}

