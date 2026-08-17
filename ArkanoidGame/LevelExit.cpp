#include "LevelExit.h"

namespace RoguelikeGame
{
	LevelExit::LevelExit(const XYZEngine::Vector2Df& position, int textureMapIndex)
	{
		gameObject = XYZEngine::GameWorld::Instance()->CreateGameObject("Door");
		auto transform = gameObject->GetComponent<XYZEngine::TransformComponent>();
		transform->SetWorldPosition(position);
	}

	XYZEngine::GameObject* LevelExit::GetGameObject()
	{
 		return gameObject;
	}
}