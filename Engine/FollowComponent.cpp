#include "pch.h"
#include "FollowComponent.h"

namespace XYZEngine
{
	FollowComponent::FollowComponent(GameObject* gameObject) : Component(gameObject)
	{

	}
	FollowComponent::~FollowComponent()
	{
		if (followTarget)
		{
			auto health = followTarget->GetComponent<HealthComponent>();
			if (health)
			{
				health->UnsubscribeDeath([this]() {
					followTarget = nullptr;
					});
			}
		}
	}
	void FollowComponent::Update(float deltaTime)
	{
		if (!followTarget || !followTarget->IsAlive())
		{
			followTarget = nullptr;
			return;
		}

		auto targetPos = followTarget->GetComponent<TransformComponent>()->GetWorldPosition();
		auto myPos = gameObject->GetComponent<TransformComponent>()->GetWorldPosition();

		int attackRadius = 0;

		auto attack = gameObject->GetComponent<MeleeAttackComponent>();
		auto rAttack = gameObject->GetComponent<RangeAttackComponent>();
		if (attack)
		{
			attackRadius = attack->GetAttackRadius();
		}
		else if (rAttack)
		{
			attackRadius = rAttack->GetAttackRadius();
		}
		else
		{
			auto sAttack = gameObject->GetComponent<BossSummonComponent>();
			if (sAttack)
				attackRadius = sAttack->GetAttackRadius();
		}

		Vector2Df direction = { targetPos.x - myPos.x, targetPos.y - myPos.y };

		float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

		if (length > attackRadius && length < detectionRadius)
		{
			direction.x /= length;
			direction.y /= length;
		}
		else
		{
			direction.x = 0;
			direction.y = 0;
		}

		auto body = gameObject->GetComponent<RigidbodyComponent>();
		body->SetLinearVelocity({ direction.x * followSpeed, direction.y * followSpeed });
	}
	void FollowComponent::Render()
	{

	}
	void FollowComponent::SetFollowTarget(GameObject* target)
	{
		followTarget = target;
		auto health = target->GetComponent<HealthComponent>();
		if (health)
		{
			health->SubscribeDeath([this]() {
				followTarget = nullptr;
				});
		}
	}
	Vector2Df FollowComponent::GetTargetPosition() const
	{
		auto transform = followTarget->GetComponent<XYZEngine::TransformComponent>();
		return transform->GetWorldPosition();
	}

	void FollowComponent::SetRadius(float radius)
	{
		detectionRadius = radius;
	}

	void FollowComponent::SetSpeed(float speed)
	{
		followSpeed = speed;
	}
}