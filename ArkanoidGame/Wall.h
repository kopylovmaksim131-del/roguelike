#pragma once

#include "CameraComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "GameObject.h"

namespace RoguelikeGame
{
	class Wall : public XYZEngine::Component
	{

	public:
		Wall(XYZEngine::GameObject* gameObject);

		void Update(float deltaTime) override;

		void Render() override {}

	};
}

