#include "pch.h"
#include "InputComponent.h"

namespace XYZEngine
{
	InputComponent::InputComponent(GameObject* gameObject) : Component(gameObject) {}

	void InputComponent::Update(float deltaTime)
	{
		verticalAxis = 0.f;
		horizontalAxis = 0.f;

		auto attack = gameObject->GetComponent<MeleeAttackComponent>();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			verticalAxis += 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			verticalAxis -= 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			horizontalAxis += 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			horizontalAxis -= 1.0f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			attackButtonPress = true;
		}
		bool isHealPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Num1);
		if (isHealPressed && !previousHealPotionState)
		{
			useHealPotion = true;
		}
		previousHealPotionState = isHealPressed;

		bool isArmorPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Num2);
		if (isArmorPressed && !previousArmorPotionState)
		{
			useArmorPotion = true;
		}
		previousArmorPotionState = isArmorPressed;

		bool isSpeedPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Num3);
		if (isSpeedPressed && !previousSpeedPotionState)
		{
			useSpeedPotion = true;
		}
		previousSpeedPotionState = isSpeedPressed;

		bool isStrengthPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Num4);
		if (isStrengthPressed && !previousStrengthPotionState)
		{
			useStrenghtPotion = true;
		}
		previousStrengthPotionState = isStrengthPressed;
	}
	void InputComponent::Render()
	{

	}

	float InputComponent::GetHorizontalAxis() const
	{
		return horizontalAxis;
	}

	float InputComponent::GetVerticalAxis() const
	{
		return verticalAxis;
	}

	void InputComponent::SetAttackButton(bool attackButton)
	{
		attackButtonPress = attackButton;
	}

	bool InputComponent::GetAttackButton()
	{
		return attackButtonPress;
	}

	bool InputComponent::GetUseHealPotion()
	{
		return useHealPotion;
	}

	void InputComponent::SetUseHealPotion()
	{
		useHealPotion = false;
	}

	bool InputComponent::GetUseArmorPotion()
	{
		return useArmorPotion;
	}

	void InputComponent::SetUseArmorPotion()
	{
		useArmorPotion = false;
	}

	bool InputComponent::GetUseSpeedPotion()
	{
		return useSpeedPotion;
	}

	void InputComponent::SetUseSpeedPotion()
	{
		useSpeedPotion = false;
	}

	bool InputComponent::GetUseStrenghtPotion()
	{
		return useStrenghtPotion;
	}

	void InputComponent::SetUseStrenghtPotion()
	{
		useStrenghtPotion = false;
	}
}