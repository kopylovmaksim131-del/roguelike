#include "MeleeEnemy.h"

namespace RoguelikeGame
{
	MeleeEnemy::MeleeEnemy(const XYZEngine::Vector2Df& position, int textureMapIndex, XYZEngine::GameObject* player)
		: Enemy(position, textureMapIndex, player)
	{
		auto hp = gameObject->GetComponent<XYZEngine::HealthComponent>();
		hp->SetHP(1);
		hp->SetMaxHP(70);

		auto armor = gameObject->GetComponent<XYZEngine::ArmorComponent>();
		armor->SetArmore(1);

		auto attack = gameObject->GetComponent<XYZEngine::MeleeAttackComponent>();
		attack->SetAttackRadius(150.f);
		attack->SetAttackCooldownTime(1.5f);
		attack->SetDamage(10);
	}
}