#include "pch.h"
#include "FollowComponent.h"

namespace XYZEngine
{
	FollowComponent::FollowComponent(GameObject* gameObject) : Component(gameObject)
	{

	}
	void FollowComponent::Update(float deltaTime)
	{
		if (!followTarget) return;

		auto targetPos = followTarget->GetComponent<TransformComponent>()->GetWorldPosition();
		auto myPos = gameObject->GetComponent<TransformComponent>()->GetWorldPosition();

		Vector2Df direction = { targetPos.x - myPos.x, targetPos.y - myPos.y };

		float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		
		if (length > 0 && length < detectionRadius)
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