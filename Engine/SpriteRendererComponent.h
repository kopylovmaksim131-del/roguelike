#pragma once

#include "TransformComponent.h"
#include "Vector.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "Export.h"

namespace XYZEngine
{
	class ENGINE_API SpriteRendererComponent : public Component
	{
	public:
		SpriteRendererComponent(GameObject* gameObject);
		~SpriteRendererComponent();

		void Update(float deltaTime) override;
		void Render() override;

		const sf::Sprite* GetSprite() const;
		sf::Sprite* GetSpriteToChange();
		void SetTexture(const sf::Texture& newTexture);
		void SetPixelSize(int newWidth, int newHeight);

		void setAlfaSpriteColor(float alfa);

		void FlipX(bool flip);
		void FlipY(bool flip);
	private:
		Vector2Df scale;
		sf::Sprite* sprite;
		TransformComponent* transform;

		bool isFlipX = false;
		bool isFlipY = false;
	};
}