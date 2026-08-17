#pragma once
#include "GameObject.h"
#include "Export.h" 

namespace XYZEngine
{
    class ENGINE_API BossSpecial
    {
    public:
        virtual void Execute(GameObject* boss, GameObject* target) = 0;
        virtual float GetCooldown() const = 0;
    };
}