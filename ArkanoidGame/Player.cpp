#include "Player.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>

namespace RoguelikeGame
{
	Player::Player(XYZEngine::GameObject* gameObject) : XYZEngine::Component(gameObject)
	{
		auto playerRenderer = gameObject->AddComponent<XYZEngine::SpriteRendererComponent>();
		playerRenderer->SetTexture(*XYZEngine::ResourceSystem::Instance()->GetTextureShared("ball"));
		playerRenderer->SetPixelSize(32, 32);

		auto playerCamera = gameObject->AddComponent<XYZEngine::CameraComponent>();
		playerCamera->SetWindow(&XYZEngine::RenderSystem::Instance()->GetMainWindow());
		playerCamera->SetBaseResolution(1280, 720);

		auto playerInput = gameObject->AddComponent<XYZEngine::InputComponent>();

		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		transform->SetWorldPosition({ 640.f, 360.f });

		auto body = gameObject->AddComponent<XYZEngine::RigidbodyComponent>();

		auto collider = gameObject->AddComponent<XYZEngine::SpriteColliderComponent>();

		auto hp = gameObject->AddComponent<XYZEngine::HealthComponent>();
		hp->SetHP(100);
		hp->SetMaxHP(100);

		auto armore = gameObject->AddComponent<XYZEngine::ArmorComponent>();
		armore->SetArmore(20);
		armore->SetMaxArmore(60);

		auto attack = gameObject->AddComponent<XYZEngine::MeleeAttackComponent>();
		attack->SetAttackRadius(75.f);
		attack->SetAttackCooldownTime(1.f);
		attack->SetDamage(15);
	}

	void Player::Update(float deltaTime)
	{
		auto input = gameObject->GetComponent<XYZEngine::InputComponent>();
		auto rigidbody = gameObject->GetComponent<XYZEngine::RigidbodyComponent>();

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
			attack->SetShouldAttack(true);
			attack->SetTargets(attack->FindTargets(lastHorizontalAxis, lasVerticalAxis));
			input->SetAttackButton(false);
		}

	}
}