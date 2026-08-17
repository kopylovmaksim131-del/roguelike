#pragma once
#include "Component.h"
#include "GameWorld.h"

namespace XYZEngine
{
	class ENGINE_API LifetimeComponent : public Component
	{
	public:
		LifetimeComponent(GameObject* gameObject);
		~LifetimeComponent();

		void Update(float deltaTime) override;
		void Render() override;

	private:
		float selfDestructTimer = 3.f;
	};
}
