#include "Loot.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>
#include "Player.h"
#include "Engine.h"

namespace RoguelikeGame
{
	Loot::Loot(const XYZEngine::Vector2Df& position, LootType type, std::string textureName)
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Loot");
		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		transform->SetWorldPosition(position);

		auto renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared(textureName));
		renderer->SetPixelSize(100, 100);

		auto rigidbody = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();
		rigidbody->SetKinematic(true);

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();
		collider->SetTrigger(true);
		collider->SubscribeTriggerEnter([this](XYZEngine::Trigger trigger) {
			auto otherObj = trigger.GetSecond()->GetGameObject();
			auto first = trigger.GetFirst()->GetGameObject();
			if (first->GetName() == "Player" || otherObj->GetName() == "Player")
			{
				Player::Instance()->GetInventory()->AddLoot(this->type);
				XYZEngine::Engine::Instance()->LogInfo("Picked up: " + LootTypeToString(this->type) + ". Total: " + std::to_string(Player::Instance()->GetInventory()->GetCount(this->type)));
				XYZEngine::GameWorld::Instance()->DestroyGameObject(gameObject);
			}
			});

		this->type = type;
	}

	std::string Loot::LootTypeToString(LootType type)
	{
		switch (type)
		{
		case HealingPotion:
			return "Healing Potion";
		case StrengthPotion:
			return "Strength Potion";
		case ArmorePotion:
			return "Armor Potion";
		case SpeedPotion:
			return "Speed Potion";
		default: return "Unknown";
		}
	}
}