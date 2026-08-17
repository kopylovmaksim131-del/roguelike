#include "Player.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>

namespace RoguelikeGame
{
	Player* Player::Instance()
	{
		static Player instance;
		return &instance;
	}

	void Player::Init(const XYZEngine::Vector2Df& position, int textureMapIndex)
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Player");
		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		transform->SetWorldPosition(position);

		auto renderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureMapElementShared("player", textureMapIndex));
		renderer->SetPixelSize(100, 100);

		auto playerCamera = gameObject->AddComponent<XYZEngine::CameraComponent>();
		playerCamera->SetWindow(&XYZEngine::RenderSystem::Instance()->GetMainWindow());
		playerCamera->SetBaseResolution(1280, 720);

		auto playerInput = gameObject->AddComponent<XYZEngine::InputComponent>();

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();

		auto hp = gameObject->AddComponent<XYZEngine::HealthComponent>();
		hp->SetHP(currentHealth);
		hp->SetMaxHP(maxHealth);
		hp->SubscribeDeath([this]() {
			gameObject = nullptr;
			});

		auto armore = gameObject->AddComponent<XYZEngine::ArmorComponent>();
		armore->SetArmore(currentArmor);
		armore->SetMaxArmore(maxArmor);

		auto attack = gameObject->AddComponent<XYZEngine::MeleeAttackComponent>();
		attack->SetAttackRadius(220.f);
		attack->SetAttackCooldownTime(0.8f);
		attack->SetDamage(damage);

		auto animation = gameObject->AddComponent<XYZEngine::AnimationComponent>();
		animation->SetAnimation("player", 0.1f, 4);

		if (!inventory)
			inventory = std::make_unique<Inventory>(this);
	}

	void Player::Update(float deltaTime)
	{
		if (!gameObject || !gameObject->IsAlive()) return;

		auto input = gameObject->GetComponent<XYZEngine::InputComponent>();
		auto rigidbody = gameObject->GetComponent<XYZEngine::RigidbodyComponent>();

		if (input && rigidbody)
		{
			rigidbody->SetLinearVelocity({
				input->GetHorizontalAxis() * speed,
				input->GetVerticalAxis() * speed
				});

			if (input->GetHorizontalAxis() != 0 || input->GetVerticalAxis() != 0)
			{
				lastHorizontalAxis = input->GetHorizontalAxis();
				lasVerticalAxis = input->GetVerticalAxis();
			}

			if (input->GetAttackButton())
			{
				auto attack = gameObject->GetComponent<XYZEngine::MeleeAttackComponent>();
				if (attack)
				{
					attack->SetShouldAttack(true);
					attack->SetTargets(attack->FindTargets(lastHorizontalAxis, lasVerticalAxis));
					input->SetAttackButton(false);
				}
			}

			if (input->GetUseHealPotion())
			{
				input->SetUseHealPotion();
				inventory->UseHealPotion();
			}

			if (input->GetUseArmorPotion())
			{
				input->SetUseArmorPotion();
				inventory->UseArmorPotion();
			}

			if (input->GetUseSpeedPotion())
			{
				input->SetUseSpeedPotion();
				inventory->UseSpeedPotion();
			}

			if (input->GetUseStrenghtPotion())
			{
				input->SetUseStrenghtPotion();
				inventory->UseStrenghtPotion();
			}
		}
	}

	XYZEngine::GameObject* Player::GetPlayerGameObject()
	{
		return gameObject;
	}

	Inventory* Player::GetInventory()
	{
		return inventory.get();
	}

	void Player::IncreaseSpeed(float increaseValue)
	{
		speed += increaseValue;
	}

	void Player::IncreaseDamage(int increaseValue)
	{
		damage += increaseValue;
		if (gameObject)
		{
			auto attack = gameObject->GetComponent<XYZEngine::MeleeAttackComponent>();
			if (attack)
				attack->SetDamage(damage);
		}
	}

	void Player::IncreaseHealth(int increaseValue)
	{
		currentHealth = std::min(maxHealth, currentHealth + increaseValue);
		if (gameObject)
		{
			auto health = gameObject->GetComponent<XYZEngine::HealthComponent>();
			if (health)
				health->RestoreHP(increaseValue);
		}
	}

	void Player::IncreaseArmor(int increaseValue)
	{
		currentArmor = std::min(maxArmor, currentArmor + increaseValue);
		if (gameObject)
		{
			auto armor = gameObject->GetComponent<XYZEngine::ArmorComponent>();
			if (armor)
				armor->RestoreArmore(increaseValue);
		}
	}
}

