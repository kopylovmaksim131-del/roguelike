#include "Player.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>

namespace RoguelikeGame
{
	Player::Player(const XYZEngine::Vector2Df& position, int textureMapIndex)
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
		hp->SetHP(100);
		hp->SetMaxHP(100);
		hp->SubscribeDeath([this]() {
			gameObject = nullptr;
			});

		auto armore = gameObject->AddComponent<XYZEngine::ArmorComponent>();
		armore->SetArmore(20);
		armore->SetMaxArmore(60);

		auto attack = gameObject->AddComponent<XYZEngine::MeleeAttackComponent>();
		attack->SetAttackRadius(220.f);
		attack->SetAttackCooldownTime(1.f);
		attack->SetDamage(15);

		auto animation = gameObject->AddComponent<XYZEngine::AnimationComponent>();
		animation->SetAnimation("player", 0.1f, 2);
	}

	void Player::Update(float deltaTime)
	{
		if (!gameObject || !gameObject->IsAlive()) return;

		auto input = gameObject->GetComponent<XYZEngine::InputComponent>();
		auto rigidbody = gameObject->GetComponent<XYZEngine::RigidbodyComponent>();

		if (input && rigidbody)
		{
			float speed = 400.0f;
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
		}

		animationTimer += deltaTime;
		if (animationTimer >= frameDuration)
		{
			animationTimer = 0.f;
			currentFrame = (currentFrame + 1) % totalFrames;

			auto renderer = gameObject->GetComponent<XYZEngine::SpriteRendererComponent>();
			if (renderer)
			{
				renderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureMapElementShared("player", currentFrame));
			}
		}
	}
	XYZEngine::GameObject* Player::GetPlayerGameObject()
	{
		return gameObject;
	}
}