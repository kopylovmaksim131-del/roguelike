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
#include "AnimationComponent.h"
#include "Inventory.h"

namespace RoguelikeGame
{
	class Player
	{
	public:
		static Player* Instance();
		void Init(const XYZEngine::Vector2Df& position, int textureMapIndex);
		void Update(float delta);
		XYZEngine::GameObject* GetPlayerGameObject();
		Inventory* GetInventory();
		void IncreaseSpeed(float increaseValue);
		void IncreaseDamage(int increaseValue);
		void IncreaseHealth(int increaseValue);
		void IncreaseArmor(int increaseValue);

	private:
		Player() = default;
		XYZEngine::GameObject* gameObject = nullptr;
		std::unique_ptr<Inventory> inventory;
		float lastHorizontalAxis = 0.f;
		float lasVerticalAxis = 0.f;
		float speed = 400.f;
		int damage = 20;
		int currentHealth = 100;
		int maxHealth = 100;
		int currentArmor = 30;
		int maxArmor = 60;
	};
}
