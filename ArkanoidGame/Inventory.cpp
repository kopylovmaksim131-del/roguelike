#include "Inventory.h"
#include "Player.h"
#include "Engine.h"

namespace RoguelikeGame
{
	Inventory::Inventory(Player* owner)
	{
		this->owner = owner;
	}

	void Inventory::AddLoot(LootType type)
	{
		if (inventoryContents.count(type))
		{
			inventoryContents[type]++;
		}
		else
		{
			inventoryContents[type] = 1;
		}
	}

	void Inventory::UseHealPotion()
	{
		if (inventoryContents[LootType::HealingPotion] <= 0)
		{
			XYZEngine::Engine::Instance()->LogInfo("No potion left");
			return;
		}
		owner->IncreaseHealth(30);
		XYZEngine::Engine::Instance()->LogInfo("Used Healing Potion. HP restored by 30");

		inventoryContents[LootType::HealingPotion]--;
		if (inventoryContents[LootType::HealingPotion] <= 0)
			inventoryContents.erase(LootType::HealingPotion);
	}

	void Inventory::UseArmorPotion()
	{
		if (inventoryContents[LootType::ArmorePotion] <= 0)
		{
			XYZEngine::Engine::Instance()->LogInfo("No potion left");
			return;
		}
		owner->IncreaseArmor(20);
		XYZEngine::Engine::Instance()->LogInfo("Used Armor Potion. Armor restored by 20");

		inventoryContents[LootType::ArmorePotion]--;
		if (inventoryContents[LootType::ArmorePotion] <= 0)
			inventoryContents.erase(LootType::ArmorePotion);
	}

	void Inventory::UseSpeedPotion()
	{
		if (inventoryContents[LootType::SpeedPotion] <= 0)
		{
			XYZEngine::Engine::Instance()->LogInfo("No potion left");
			return;
		}

		owner->IncreaseSpeed(50);
		XYZEngine::Engine::Instance()->LogInfo("Used Speed Potion");

		inventoryContents[LootType::SpeedPotion]--;
		if (inventoryContents[LootType::SpeedPotion] <= 0)
			inventoryContents.erase(LootType::SpeedPotion);

	}

	void Inventory::UseStrenghtPotion()
	{
		if (inventoryContents[LootType::StrengthPotion] <= 0)
		{
			XYZEngine::Engine::Instance()->LogInfo("No potion left");
			return;
		}
		owner->IncreaseDamage(10);
		XYZEngine::Engine::Instance()->LogInfo("Used Strength Potion. Damage increased by 10");

		inventoryContents[LootType::StrengthPotion]--;
		if (inventoryContents[LootType::StrengthPotion] <= 0)
			inventoryContents.erase(LootType::StrengthPotion);
	}

	int Inventory::GetCount(LootType type)
	{
		return inventoryContents[type];
	}
}