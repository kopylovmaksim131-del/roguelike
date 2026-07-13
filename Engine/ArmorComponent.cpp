#include "pch.h"
#include "ArmorComponent.h"

namespace XYZEngine
{
	ArmorComponent::ArmorComponent(GameObject* gameObject) : Component(gameObject)
	{
	}
	ArmorComponent::~ArmorComponent()
	{
	}
	void ArmorComponent::Update(float deltaTime)
	{
	}
	void ArmorComponent::Render()
	{
	}
	void ArmorComponent::SetArmore(int value)
	{
		Armore = value;
	}
	void ArmorComponent::SetMaxArmore(int value)
	{
		maxArmore = value;
	}
	int ArmorComponent::TakeDamage(int damage)
	{
		if (damage <= 0)
		{
			return 0;
		}

		int dif = std::min(damage, Armore);  
		Armore -= dif;
		return damage - dif;
	}
	void ArmorComponent::RestoreArmore(int value)
	{
		if (value > 0)
		{
			Armore = std::min(maxArmore, Armore + value);
		}
	}
	int ArmorComponent::GetArmore()
	{
		return Armore;
	}
}