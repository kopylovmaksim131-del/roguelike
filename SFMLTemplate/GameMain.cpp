// ©2023, XYZ School. All rights reserved.
// Authored by Aleksandr Rybalka (polterageist@gmail.com)

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Engine.h"
#include "Windows.h"
#include <iostream>
#include "ResourceSystem.h"
#include "RenderSystem.h"

const std::string RESOURCES_PATH = "Resources/";

int main()
{
	XYZEngine::RenderSystem::Instance()->SetMainWindow(new sf::RenderWindow(sf::VideoMode(1280, 720), "XYZRoguelike"));

	XYZEngine::ResourceSystem::Instance()->LoadTexture("ball", "Resources/Textures/ball.png");

	XYZEngine::Engine::Instance()->Run();

	sf::RenderWindow window(sf::VideoMode(330, 400), "SFML works!");

	sf::Texture logo;
	if (!logo.loadFromFile(RESOURCES_PATH + "xyz-logo.png"))
	{
		return EXIT_FAILURE;
	}
	sf::Sprite logo_sprite(logo);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(logo_sprite);
		window.display();
	}

	return 0;
}
