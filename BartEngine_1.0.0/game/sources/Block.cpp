#include <Block.h>
#include <Engine.h>
#include "MathHelper.h"

Block::Block()
{
    const unsigned tSeed = static_cast<unsigned>(bart::Engine::Instance().GetTimer().GetTime());
    srand(tSeed);
}

void Block::SetBlock(const int aBlock)
{
    m_BlockID = aBlock;
}

int Block::NextRotation(const int aRotation) const
{
    int tRotation = aRotation + 1;
    const int tSize = static_cast<int>(Data[m_BlockID].size()) - 1;
    if (tRotation > tSize - 1)
    {
        tRotation = 0;
    }

    return tRotation;
}

int Block::RandomBlock(const bool aRepetitionAllowed) const
{
    int tRandom = bart::MathHelper::RandomRange(0, Data.size() - 1);

    if (!aRepetitionAllowed)
    {
        while (tRandom == m_BlockID)
        {
            tRandom = bart::MathHelper::RandomRange(0, Data.size() - 1);
        }
    }

    return tRandom;
}
