#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include "Component.h"
#include "Collision.h"
#include "Trigger.h"
#include "PhysicsSystem.h"
#include "MeleeAttackComponent.h"
#include "Export.h"

namespace XYZEngine
{
	class ENGINE_API FollowComponent : public Component
	{
	public:
		FollowComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;
		void SetFollowTarget(GameObject* target);
		Vector2Df GetTargetPosition() const;
		void SetRadius(float radius);
		void SetSpeed(float speed);

	protected:
		GameObject* followTarget = nullptr;

	private:
		float detectionRadius = 200.f;
		float followSpeed = 150.f;
	};
}