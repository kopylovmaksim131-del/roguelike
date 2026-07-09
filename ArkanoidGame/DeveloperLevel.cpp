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
		ResourceSystem::Instance()->LoadTexture("Background", "Resources/Textures/Background.png");

		auto background = XYZEngine::GameWorld::Instance()->CreateGameObject("Background");
		background->AddComponent<RoguelikeGame::Background>();

		auto leftWall = XYZEngine::GameWorld::Instance()->CreateGameObject("LeftWall");
		leftWall->AddComponent<RoguelikeGame::Wall>();
		auto renderLW = leftWall->GetComponent<XYZEngine::SpriteRendererComponent>();
		renderLW->SetPixelSize(32, 720);
		auto transformLW = leftWall->GetComponent<XYZEngine::TransformComponent>();
		transformLW->SetWorldPosition(16.f, 360.f);
		
		auto rightWall = XYZEngine::GameWorld::Instance()->CreateGameObject("RightWall");
		rightWall->AddComponent<RoguelikeGame::Wall>();
		auto renderRW = rightWall->GetComponent<XYZEngine::SpriteRendererComponent>();
		renderRW->SetPixelSize(32, 720);
		auto transformRW = rightWall->GetComponent<XYZEngine::TransformComponent>();
		transformRW->SetWorldPosition(1264.f, 360.f);
		
		auto upperWall = XYZEngine::GameWorld::Instance()->CreateGameObject("UpperWall");
		upperWall->AddComponent<RoguelikeGame::Wall>();
		auto renderUW = upperWall->GetComponent<XYZEngine::SpriteRendererComponent>();
		renderUW->SetPixelSize(1280, 32);
		auto transformUW = upperWall->GetComponent<XYZEngine::TransformComponent>();
		transformUW->SetWorldPosition(640.f, 16.f);
		
		auto lowerWall = XYZEngine::GameWorld::Instance()->CreateGameObject("LowerWall");
		lowerWall->AddComponent<RoguelikeGame::Wall>();
		auto render = lowerWall->GetComponent<XYZEngine::SpriteRendererComponent>();
		render->SetPixelSize(1280, 32);
		auto transform = lowerWall->GetComponent<XYZEngine::TransformComponent>();
		transform->SetWorldPosition(640.f, 704.f);
		
		auto player = XYZEngine::GameWorld::Instance()->CreateGameObject("Player");
		player->AddComponent<RoguelikeGame::Player>();

		auto enemy = XYZEngine::GameWorld::Instance()->CreateGameObject("Enemy");
		enemy->AddComponent<RoguelikeGame::Enemy>();
		auto follow = enemy->AddComponent<XYZEngine::FollowComponent>();
		follow->SetFollowTarget(player);
		follow->SetRadius(240.f);
		follow->SetSpeed(200.f);

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
}