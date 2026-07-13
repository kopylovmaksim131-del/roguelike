#include "pch.h"
#include "CameraComponent.h"
#include "TransformComponent.h"

namespace XYZEngine
{
	CameraComponent::CameraComponent(GameObject* gameObject) : Component(gameObject)
	{
		view = new sf::View(sf::FloatRect(0, 0, 800, -600));
		transform = gameObject->GetComponent<TransformComponent>();
	}
	CameraComponent::~CameraComponent()
	{
		delete view;
	}

	void CameraComponent::Update(float deltaTime)
	{
		auto position = transform->GetWorldPosition();
		auto rotation = transform->GetWorldRotation();

		view->setCenter(Convert<sf::Vector2f, Vector2Df>(position));
		view->setRotation(rotation);

		window->setView(*view);
	}
	void CameraComponent::Render()
	{
		if (window == nullptr)
		{
			std::cout << "NULL window render." << std::endl;
		}
	}

	void CameraComponent::SetBaseResolution(int width, int height)
	{
		view->reset(sf::FloatRect(0, 0, (float)width, (float) - height));
	}
	void CameraComponent::SetWindow(sf::RenderWindow* newWindow)
	{
		window = newWindow;
	}
	void CameraComponent::ZoomBy(float newZoom)
	{
		if (newZoom <= 0)
		{
			LOG_WARN("CameraComponent::ZoomBy: zoom value must be > 0, got " + std::to_string(newZoom));
			return;
		}
		view->zoom(newZoom);
	}
}