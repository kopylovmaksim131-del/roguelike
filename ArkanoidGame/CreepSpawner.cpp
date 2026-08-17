#include "CreepSpawner.h"

namespace RoguelikeGame
{
    void CreepSpawner::SpawnCreeps(EnemyType type, int count, XYZEngine::GameObject* player, std::vector<std::pair<int, int>>& freeCells)
    {
        for (int i = 0; i < count; i++)
        {
            if (freeCells.empty()) break;

            int index = std::rand() % freeCells.size();
            std::pair<int, int> cell = freeCells[index];
            int x = cell.first;
            int y = cell.second;
            if (index < freeCells.size())
            {
                freeCells.erase(freeCells.begin() + index);
            }
            XYZEngine::Vector2Df position{ x * 128.f, y * 128.f };
            factory->Create(type, position, player);
        }
    }

}
