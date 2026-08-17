#include "RangeEnemy.h"

namespace RoguelikeGame
{
	RangeEnemy::RangeEnemy(const XYZEngine::Vector2Df& position, int textureMapIndex, XYZEngine::GameObject* player)
		: Enemy(position, textureMapIndex, player)
	{
		auto hp = gameObject->GetComponent<XYZEngine::HealthComponent>();
		hp->SetHP(35);
		hp->SetMaxHP(35);

		auto armor = gameObject->GetComponent<XYZEngine::ArmorComponent>();
		armor->SetArmore(5);

		auto attack = gameObject->AddComponent<XYZEngine::RangeAttackComponent>();
		attack->SetTargets(std::vector< XYZEngine::GameObject*> { player });
		attack->SetAttackMode(true);
		attack->SetAttackRadius(550.f);
		attack->SetAttackCooldownTime(1.5f);
		attack->SetDamage(12);
	}
}