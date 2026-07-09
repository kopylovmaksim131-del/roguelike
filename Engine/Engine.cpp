#include "pch.h"
#include "Engine.h"
#include <SFML/Graphics.hpp>
#include <iostream>

Engine::Engine() {}

void Engine::Initialization()
{
	std::cout << "Engine init" << std::endl;
}

void Engine::Run()
{
	std::cout << "Engine run" << std::endl;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Test SFML from Engine");

   while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.display();
    }
}