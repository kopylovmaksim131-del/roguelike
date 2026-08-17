#include "pch.h"
#include "LifetimeComponent.h"

namespace XYZEngine
{
	LifetimeComponent::LifetimeComponent(GameObject* gameObject) : Component(gameObject)
	{
	}
	LifetimeComponent::~LifetimeComponent()
	{
	}
	void LifetimeComponent::Update(float deltaTime)
	{
		selfDestructTimer -= deltaTime;

		if (selfDestructTimer <= 0.f)
			GameWorld::Instance()->DestroyGameObject(gameObject);
	}
	void LifetimeComponent::Render()
	{
	}
}