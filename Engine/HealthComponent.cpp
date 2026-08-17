#include "pch.h"
#include "HealthComponent.h"

namespace XYZEngine
{
	HealthComponent::HealthComponent(GameObject* gameObject) : Component(gameObject)
	{
	}
	HealthComponent::~HealthComponent()
	{
	}
	void HealthComponent::Update(float deltaTime)
	{
		if (healthPoint == 0 && maxHealthPoint > 0)
		{
			LOG_INFO("HealthComponent: calling " + std::to_string(deathSubscribers.size()) + " death subscribers");
			for (auto& subscriber : deathSubscribers)
			{
				subscriber(); 
			}
			GameWorld::Instance()->DestroyGameObject(gameObject);
		}
	}
	void HealthComponent::Render()
	{
	}
	void HealthComponent::SetHP(int hp)
	{
		healthPoint = hp;
	}
	void HealthComponent::SetMaxHP(int maxHp)
	{
		maxHealthPoint = maxHp;
	}
	void HealthComponent::TakeDamage(int damage)
	{
		auto name = gameObject->GetName();
		LOG_INFO("HealthComponent::TakeDamage object name='" + name + "', take damage='" + std::to_string(damage));
		if (damage > 0)
		{
			healthPoint = std::max(0, healthPoint - damage);
		}
	}
	void HealthComponent::RestoreHP(int hp)
	{
		if (hp > 0)
		{
			healthPoint = std::min(maxHealthPoint, healthPoint + hp);
		}
	}
	int HealthComponent::GetHP()
	{
		return healthPoint;
	}
	void HealthComponent::SubscribeDeath(std::function<void()> onDeath)
	{
		deathSubscribers.push_back(onDeath);
	}
	void HealthComponent::UnsubscribeDeath(std::function<void()> onDeath)
	{
		deathSubscribers.erase(
			std::remove_if(deathSubscribers.begin(), deathSubscribers.end(),
				[&onDeath](const std::function<void()>& stored) {
					return stored.target<void()>() == onDeath.target<void()>();
				}),
			deathSubscribers.end()
		);
	}
}