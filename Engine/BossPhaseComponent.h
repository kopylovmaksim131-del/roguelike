#pragma once
#include "Component.h"
#include "HealthComponent.h"
#include "SpriteRendererComponent.h"
#include "Export.h"

namespace XYZEngine
{
    class ENGINE_API BossPhaseComponent : public Component
    {
    public:
        BossPhaseComponent(GameObject* gameObject);
        void Update(float deltaTime) override;
        void Render() override {}

        bool IsSecondPhase() const { return secondPhase; }

    private:
        bool secondPhase = false;
    };
}