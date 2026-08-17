#include "CreepFactory.h"
#include "GameObject.h"

namespace RoguelikeGame
{
	void CreepFactory::Create(EnemyType type, const XYZEngine::Vector2Df& position, XYZEngine::GameObject* player)
	{
		switch (type)
		{
		case EnemyType::Melee:
			new MeleeEnemy(position, 0, player);
			break;
		case EnemyType::Range:
			new RangeEnemy(position, 0, player);
			break;
		}
	}
}