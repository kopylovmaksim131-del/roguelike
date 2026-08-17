#pragma once
#include <memory>
#include <array>
#include "Vector.h"
#include "CameraComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "HealthComponent.h"
#include "ArmorComponent.h"
#include "MeleeAttackComponent.h"
#include "GameObject.h"
#include "CreepFactory.h"

namespace RoguelikeGame
{
    class CreepSpawner {
    
    public:
        CreepSpawner(CreepFactory* factory) : factory(factory) {};
        void SpawnCreeps(EnemyType type, int count, XYZEngine::GameObject* player, std::vector<std::pair<int, int>>& freeCells);

    private:
        CreepFactory* factory;
    };

}