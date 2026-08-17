#pragma once
#include "GameObject.h"
#include "Enemy.h"
#include "MeleeEnemy.h"
#include "RangeEnemy.h"
#include "MageBoss.h"
#include "SummonBoss.h"

namespace RoguelikeGame
{
    enum EnemyType
    {
        Melee,
        Range,
        Mage,
        Summoner
    };

    class CreepFactory
    {
    public:
        void Create(EnemyType type, const XYZEngine::Vector2Df& position, XYZEngine::GameObject* player);

    };

}