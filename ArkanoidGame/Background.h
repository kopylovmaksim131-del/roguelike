#pragma once

#include "CameraComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "GameObject.h"

namespace RoguelikeGame
{
	class Background : public XYZEngine::Component
	{

	public:
		Background(XYZEngine::GameObject* gameObject);

		void Update(float deltaTime) override;

		void Render() override {}

	};
}

