#pragma once
#include "Component.h"
#include "Export.h" 
#include "Logger.h"
#include "GameWorld.h"

namespace XYZEngine
{
	class ENGINE_API HealthComponent : public Component
	{
	public:
		HealthComponent(GameObject* gameObject);
		~HealthComponent();

		void Update(float deltaTime) override;
		void Render() override;

		void SetHP(int hp);
		void SetMaxHP(int maxHp);
		void TakeDamage(int damage);
		void RestoreHP(int hp);
		int GetHP();
		void SubscribeDeath(std::function<void()> onDeath);

	private:
		int healthPoint = 0;
		int maxHealthPoint = 0;
		std::vector<std::function<void()>> deathSubscribers;
	};
}