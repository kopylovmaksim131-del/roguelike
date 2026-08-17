#include "pch.h"
#include "BossPhaseComponent.h"

namespace XYZEngine
{
    BossPhaseComponent::BossPhaseComponent(GameObject* gameObject)
        : Component(gameObject) {
    }

    void BossPhaseComponent::Update(float deltaTime)
    {
        auto health = gameObject->GetComponent<HealthComponent>();
        if (!health) return;

        float hpPercent = (float)health->GetHP() / health->GetMaxHP();

        if (hpPercent <= 0.5f && !secondPhase)
        {
            secondPhase = true;

            auto render = gameObject->GetComponent<SpriteRendererComponent>();
            if (render)
                render->GetSpriteToChange()->setColor(sf::Color::Red);
        }
    }
}