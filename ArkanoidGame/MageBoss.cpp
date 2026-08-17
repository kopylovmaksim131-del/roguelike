#include "MageBoss.h"

namespace RoguelikeGame
{
	MageBoss::MageBoss(const XYZEngine::Vector2Df& position, int textureMapIndex, XYZEngine::GameObject* player)
		: Enemy(position, textureMapIndex, player)
	{
		auto hp = gameObject->GetComponent<XYZEngine::HealthComponent>();
		hp->SetHP(30);
		hp->SetMaxHP(30);

		auto armor = gameObject->GetComponent<XYZEngine::ArmorComponent>();
		armor->SetArmore(1);

		auto phase = gameObject->AddComponent<XYZEngine::BossPhaseComponent>();

		auto attack = gameObject->AddComponent<XYZEngine::BossRangeAttackComponent>();
		attack->SetTargets(std::vector< XYZEngine::GameObject*> { player });
		attack->SetAttackMode(true);
		attack->SetAttackRadius(550.f);
		attack->SetAttackCooldownTime(1.5f);
		attack->SetDamage(20);
		attack->AddSpecial(std::make_shared<XYZEngine::AOEBossSpecial>());
		attack->AddSpecial(std::make_shared<XYZEngine::DirectionalVolleyBossSpecial>());
		attack->AddSpecial(std::make_shared<XYZEngine::HomingProjectileBossSpecial>());


	}
}