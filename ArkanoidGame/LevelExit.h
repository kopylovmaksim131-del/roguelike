#pragma once

#include "CameraComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "GameObject.h"
#include <ResourceSystem.h>
#include "SpriteColliderComponent.h"

namespace RoguelikeGame
{
	class LevelExit
	{
	public:
		LevelExit(const XYZEngine::Vector2Df& position, int textureMapIndex);
		XYZEngine::GameObject* GetGameObject();
	private:
		XYZEngine::GameObject* gameObject;
	};
}

