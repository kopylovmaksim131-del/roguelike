#pragma once
#include <memory>
#include <array>
#include "Vector.h"
#include "Loot.h"
#include "GameWorld.h"
#include "GameObject.h"

namespace RoguelikeGame
{
    class LootFactory
    {
    public:
        LootFactory(LootType type, int count, std::vector<std::pair<int, int>>& freeCells, std::string textureName);
    };
}