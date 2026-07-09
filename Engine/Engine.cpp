#include "pch.h"
#include "Engine.h"
#include <iostream>
#include "GameWorld.h"
#include "RenderSystem.h"
#include "ResourceSystem.h"


namespace XYZEngine
{
	Engine* Engine::Instance()
	{
		static Engine instance;
		return &instance;
	}

	Engine::Engine()
	{
		unsigned int seed = (unsigned int)time(nullptr);
		srand(seed);
	}

	void Engine::CreateWindowNew(unsigned width, unsigned height, const std::string& title)
	{
		auto* window = new sf::RenderWindow(sf::VideoMode(width, height), title);
		RenderSystem::Instance()->SetMainWindow(window);
	}

	void Engine::PlayMusic(const std::string& name)
	{
		auto music = ResourceSystem::Instance()->GetMusicShared(name);
		music->setLoop(true);
		music->play();
	}

	void Engine::Run()
	{
		sf::Clock gameClock;
		sf::Event event;

		while (RenderSystem::Instance()->GetMainWindow().isOpen())
		{
			sf::Time dt = gameClock.restart();
			float deltaTime = dt.asSeconds();

			while (RenderSystem::Instance()->GetMainWindow().pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					RenderSystem::Instance()->GetMainWindow().close();
				}
			}

			if (!RenderSystem::Instance()->GetMainWindow().isOpen())
			{
				break;
			}

			RenderSystem::Instance()->GetMainWindow().clear();

			GameWorld::Instance()->Update(deltaTime);
			GameWorld::Instance()->FixedUpdate(deltaTime);
			GameWorld::Instance()->Render();
			GameWorld::Instance()->LateUpdate();

			RenderSystem::Instance()->GetMainWindow().display();
		}
	}
}