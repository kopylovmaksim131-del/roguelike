#pragma once

#include "Component.h"
#include "MeleeAttackComponent.h"
#include <SFML/Window.hpp> 
#include "Export.h"
#include "GameObject.h"

namespace XYZEngine
{
	class ENGINE_API InputComponent : public Component
	{
	public:
		InputComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;

		float GetHorizontalAxis() const;
		float GetVerticalAxis() const;
		void SetAttackButton(bool attackButton);
		bool GetAttackButton();
		bool GetUseHealPotion();
		void SetUseHealPotion();
		bool GetUseArmorPotion();
		void SetUseArmorPotion();
		bool GetUseSpeedPotion();
		void SetUseSpeedPotion();
		bool GetUseStrenghtPotion();
		void SetUseStrenghtPotion();
	private:
		float horizontalAxis = 0.f;
		float verticalAxis = 0.f;
		bool attackButtonPress = false;
		bool useHealPotion = false;
		bool useArmorPotion = false;
		bool useSpeedPotion = false;
		bool useStrenghtPotion = false;
		bool previousHealPotionState = false;
		bool previousArmorPotionState = false;
		bool previousSpeedPotionState = false;
		bool previousStrengthPotionState = false;

	};
}