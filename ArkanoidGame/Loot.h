#pragma once
#include "GameWorld.h"
#include "GameObject.h"
#include "Component.h"
#include "TransformComponent.h"
#include "ResourceSystem.h"
#include "SpriteColliderComponent.h"
#include "ColliderComponent.h"
#include "Trigger.h"
#include "Logger.h"

namespace RoguelikeGame
{
	enum LootType
	{
		HealingPotion,
		StrengthPotion,
		ArmorePotion,
		SpeedPotion
	};

	class Loot
	{
	public:
		Loot(const XYZEngine::Vector2Df& position, LootType type, std::string textureName);
	private:
		std::string LootTypeToString(LootType type);

		XYZEngine::GameObject* gameObject;
		LootType type;
	};
}

