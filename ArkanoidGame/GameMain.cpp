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

	XYZEngine::ResourceSystem::Instance()->LoadTextureMap("player", "Resources/TextureMaps/Player.png", { 48, 63 }, 9, false);
	XYZEngine::ResourceSystem::Instance()->LoadTextureMap("level_floors", "Resources/TextureMaps/Floor.png", { 16, 16 }, 49, false);
	XYZEngine::ResourceSystem::Instance()->LoadTextureMap("level_walls", "Resources/TextureMaps/Wall_new.png", { 16, 16 }, 48, false);

	auto developerLevel = std::make_shared<DeveloperLevel>();
	developerLevel->Start();

	XYZEngine::GameWorld::Instance()->SetActiveScene(developerLevel);
	XYZEngine::Engine::Instance()->Run();

	return 0;
}

