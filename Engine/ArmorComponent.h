#pragma once
#include "Component.h"
#include "Export.h" 
#include "Logger.h"

namespace XYZEngine
{
	class ENGINE_API ArmorComponent : public Component
	{
	public:
		ArmorComponent(GameObject* gameObject);
		~ArmorComponent();

		void Update(float deltaTime) override;
		void Render() override;

		void SetArmore(int hp);
		void SetMaxArmore(int maxHp);
		int TakeDamage(int damage);
		void RestoreArmore(int hp);
		int GetArmore();

	private:
		int Armore = 0;
		int maxArmore = 0;
	};
}