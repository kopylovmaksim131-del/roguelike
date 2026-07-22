#pragma once

#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "InputComponent.h"
#include "HealthComponent.h"
#include "ArmorComponent.h"
#include "MeleeAttackComponent.h"
#include "GameObject.h"
#include "Player.h"
#include "FollowComponent.h"

namespace RoguelikeGame
{
	class Enemy
	{
	public:
		Enemy(const XYZEngine::Vector2Df& position, int textureMapIndex, XYZEngine::GameObject* player);
	protected:
		XYZEngine::GameObject* gameObject;
	};
}

