#pragma once

#include "CameraComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "InputComponent.h"
#include "HealthComponent.h"
#include "ArmorComponent.h"
#include "MeleeAttackComponent.h"
#include "AnimationComponent.h"
#include "GameObject.h"

namespace RoguelikeGame
{
	class Player
	{
	public:
		Player(const XYZEngine::Vector2Df& position, int textureMapIndex);
		void Update(float delta);
		XYZEngine::GameObject* GetPlayerGameObject();
	private:
		XYZEngine::GameObject* gameObject;
		float lastHorizontalAxis = 0.f;
		float lasVerticalAxis = 0.f;
		float animationTimer = 0.f;
		float frameDuration = 0.1f;
		int currentFrame = 0;
		int totalFrames = 9;
	};
}

