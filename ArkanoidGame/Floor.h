#pragma once

#include "CameraComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "GameObject.h"
#include <ResourceSystem.h>

namespace RoguelikeGame
{
	class Floor
	{
	public:
		Floor(const XYZEngine::Vector2Df& position, int textureMapIndex);
	private:
		XYZEngine::GameObject* gameObject;
	};
}