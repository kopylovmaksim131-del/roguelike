#include "LootFactory.h"

namespace RoguelikeGame
{
    LootFactory::LootFactory(LootType type, int count, std::vector<std::pair<int, int>>& freeCells, std::string textureName)
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

            new Loot(position, type, textureName);
        }
    }
}
