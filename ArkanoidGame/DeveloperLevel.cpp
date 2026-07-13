#include "DeveloperLevel.h"
#include <ResourceSystem.h>
#include <Engine.h>
#include <TransformComponent.h>
#include <FollowComponent.h>

using namespace XYZEngine;

namespace RoguelikeGame
{
	void DeveloperLevel::Start()
	{
		CreatBackground();
		CreatPlayer();
		CreatEnemy();

		ResourceSystem::Instance()->LoadMusic("Sound", "Resources/Sounds/Sound.ogg");
		XYZEngine::Engine::Instance()->PlayMusic("Sound");
	}
	void DeveloperLevel::Restart()
	{
		Stop();
		Start();
	}
	void DeveloperLevel::Stop()
	{
		auto music = ResourceSystem::Instance()->GetMusicShared("Sound");
		if (music)
			music->stop();

		GameWorld::Instance()->Clear();
	}
	void DeveloperLevel::CreatPlayer()
	{
		auto player = XYZEngine::GameWorld::Instance()->CreateGameObject("Player");
		player->AddComponent<RoguelikeGame::Player>();
	}
	void DeveloperLevel::CreatEnemy()
	{
		auto player = XYZEngine::GameWorld::Instance()->GetGameObjectByName("Player");
		auto enemy = XYZEngine::GameWorld::Instance()->CreateGameObject("Enemy");
		enemy->AddComponent<RoguelikeGame::Enemy>();
		auto follow = enemy->AddComponent<XYZEngine::FollowComponent>();
		follow->SetFollowTarget(player);
		follow->SetRadius(240.f);
		follow->SetSpeed(200.f);
		auto attack = enemy->GetComponent<XYZEngine::MeleeAttackComponent>();
		attack->SetTargets(std::vector<GameObject*>{player});
	}
	void DeveloperLevel::CreatBackground()
	{
		ResourceSystem::Instance()->LoadTexture("Background", "Resources/Textures/Background.png");

		auto background = XYZEngine::GameWorld::Instance()->CreateGameObject("Background");
		background->AddComponent<RoguelikeGame::Background>();

		CreatWall("LeftWall", 16.f, 360.f, 32, 720);
		CreatWall("RightWall", 1264.f, 360.f, 32, 720);
		CreatWall("UpperWall", 640.f, 16.f, 1280, 32);
		CreatWall("LowerWall", 640.f, 704.f, 1280, 32);
	}

	void DeveloperLevel::CreatWall(const std::string& name, float x, float y, int width, int height)
	{
		auto leftWall = XYZEngine::GameWorld::Instance()->CreateGameObject(name);
		leftWall->AddComponent<RoguelikeGame::Wall>();
		auto renderLW = leftWall->GetComponent<XYZEngine::SpriteRendererComponent>();
		renderLW->SetPixelSize(width, height);
		auto transformLW = leftWall->GetComponent<XYZEngine::TransformComponent>();
		transformLW->SetWorldPosition(x, y);
	}
}