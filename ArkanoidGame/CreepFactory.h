#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "MeleeEnemy.h"
#include "RangeEnemy.h"

namespace RoguelikeGame
{
    enum EnemyType
    {
        Melee,
        Range
    };

    class CreepFactory 
    {
    public:
        void Create(EnemyType type, const XYZEngine::Vector2Df& position, XYZEngine::GameObject* player);

    };

}