#include "MeleeEnemy.h"

namespace RoguelikeGame
{
	MeleeEnemy::MeleeEnemy(const XYZEngine::Vector2Df& position, int textureMapIndex, XYZEngine::GameObject* player)
		: Enemy(position, textureMapIndex, player)
	{
		auto hp = gameObject->GetComponent<XYZEngine::HealthComponent>();
		hp->SetHP(40);
		hp->SetMaxHP(40);

		auto armor = gameObject->GetComponent<XYZEngine::ArmorComponent>();
		armor->SetArmore(5);

		auto attack = gameObject->AddComponent<XYZEngine::MeleeAttackComponent>();
		attack->SetTargets(std::vector< XYZEngine::GameObject*> { player });
		attack->SetAttackMode(true);
		attack->SetAttackRadius(150.f);
		attack->SetAttackCooldownTime(1.5f);
		attack->SetDamage(15);
	}
}