#ifndef STATS_BOX_H
#define STATS_BOX_H

#include <Entity.h>
#include <Text.h>
#include <Block.h>
#include <Atlas.h>

using namespace bart;

class StatsBox final : public Entity
{
public:
    virtual ~StatsBox() = default;
    StatsBox();

    bool CanDraw() override { return true; }
    bool CanUpdate() override { return false; }
    void Draw() override;
    void Start() override;
    void Destroy() override;

    void OnBlockPlaced(int aBlock);
    void ColorChanged(int aColor);

private:
    Text* m_StatsText{ nullptr };
    Transform* m_StatsTransform{ nullptr };

    vector<Text*> m_BlockNumbers;
    vector<Transform*> m_BlockTextTransform;

    vector<int> m_BlockCount = {0, 0, 0, 0, 0, 0, 0};

    Block m_Block;

    Transform* m_AtlasTransform{ nullptr };
    Atlas* m_BlockAtlas{ nullptr };

    const std::string BLOCK_FRAME1 = "Block1";
    const std::string BLOCK_FRAME2 = "Block2";
    const std::string BLOCK_FRAME3 = "Block3";
    const std::string BLOCK_FRAME4 = "Block4";
    const std::string BLOCK_FRAME5 = "Block5";
    const std::string BLOCK_FRAME6 = "Block6";
    const std::string BLOCK_FRAME7 = "Block7";
    const std::string BLOCK_FRAME8 = "Block8";
    const std::string BLOCK_FRAME9 = "Block9";

    vector<std::string> m_BlockFrame = {
        BLOCK_FRAME1,
        BLOCK_FRAME2,
        BLOCK_FRAME3,
        BLOCK_FRAME4,
        BLOCK_FRAME5,
        BLOCK_FRAME6,
        BLOCK_FRAME7,
        BLOCK_FRAME8,
        BLOCK_FRAME9
    };
};

#endif
