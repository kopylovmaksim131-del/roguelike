#include "Player.h"
#include "Engine.h"
#include "Logger.h"
#include "ResourceSystem.h"
#include "DeveloperLevel.h"
#include "Matrix2D.h"

using namespace RoguelikeGame;

int main()
{
	XYZEngine::Engine::Instance()->SetupLogger();

	XYZEngine::Engine::Instance()->CreateWindowNew(1280, 720, "Roguelike");
	
	XYZEngine::ResourceSystem::Instance()->LoadTexture("ball", "Resources/Textures/Ball.png");
	XYZEngine::ResourceSystem::Instance()->LoadTexture("Bonus", "Resources/Textures/Bonus.png"); 
	XYZEngine::ResourceSystem::Instance()->LoadTexture("Wall", "Resources/Textures/Wall.png");

	auto developerLevel = std::make_shared<DeveloperLevel>();
	developerLevel->Start();

	XYZEngine::Engine::Instance()->Run();

	return 0;
}

