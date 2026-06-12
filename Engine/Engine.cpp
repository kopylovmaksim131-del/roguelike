#include "pch.h"
#include "Engine.h"
//#include <SFML/Graphics.hpp>
#include <iostream>

Engine::Engine() {}

void Engine::Initialization()
{
	std::cout << "Engine init" << std::endl;
}

void Engine::Run()
{
	std::cout << "Engine run" << std::endl;
}