#include "pch.h"
#include "BossRangeAttackComponent.h"

namespace XYZEngine
{
	void BossRangeAttackComponent::AddSpecial(std::shared_ptr<BossSpecial> special)
	{
		specials.push_back(special);
	}
	void BossRangeAttackComponent::Update(float deltaTime)
	{
		RangeAttackComponent::Update(deltaTime);

		auto phase = gameObject->GetComponent<BossPhaseComponent>();
		float cooldownMultiplier = phase && phase->IsSecondPhase() ? 0.5f : 1.0f;

		specialTimer -= deltaTime;
		if (specialTimer <= 0.f && !specials.empty())
		{
			for (auto obj : attackTargets)
			{
				specials[currentSpecial]->Execute(gameObject, obj);
				specialTimer = specials[currentSpecial]->GetCooldown() * cooldownMultiplier;
				currentSpecial = (currentSpecial + 1) % specials.size();
			}
		}
	}
}