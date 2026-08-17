#pragma once
#include "GameWorld.h"
#include "Loot.h"
#include "HealthComponent.h"
#include "ArmorComponent.h"
#include "MeleeAttackComponent.h"
#include "RigidbodyComponent.h"

namespace RoguelikeGame
{
	class Player;

	class Inventory
	{
	public:
		Inventory(Player* owner);
		void AddLoot(LootType type);
		void UseLoot(int number);
		int GetCount(LootType type);
		void UseHealPotion();
		void UseArmorPotion();
		void UseSpeedPotion();
		void UseStrenghtPotion();

	private:
		Player* owner;
		std::map<LootType, int> inventoryContents;
	};
}
