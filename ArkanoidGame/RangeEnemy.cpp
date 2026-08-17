#include "RangeEnemy.h"

namespace RoguelikeGame
{
	RangeEnemy::RangeEnemy(const XYZEngine::Vector2Df& position, int textureMapIndex, XYZEngine::GameObject* player)
		: Enemy(position, textureMapIndex, player)
	{
		auto hp = gameObject->GetComponent<XYZEngine::HealthComponent>();
		hp->SetHP(40);
		hp->SetMaxHP(40);

		auto armor = gameObject->GetComponent<XYZEngine::ArmorComponent>();
		armor->SetArmore(5);

		auto attack = gameObject->GetComponent<XYZEngine::MeleeAttackComponent>();
		attack->SetAttackRadius(500.f);
		attack->SetAttackCooldownTime(1.3f);
		attack->SetDamage(6);
	}
}