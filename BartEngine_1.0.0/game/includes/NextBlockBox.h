#ifndef NEXT_BLOCK_BOX_H
#define NEXT_BLOCK_BOX_H

#include <Entity.h>
#include <Text.h>
#include <Block.h>
#include <Atlas.h>

using namespace bart;

class NextBlockBox final : public Entity
{
public:
    virtual ~NextBlockBox() = default;
    NextBlockBox();

    bool CanDraw() override { return true; }
    bool CanUpdate() override { return false; }
    void DrawNextBlock(IGraphic& aGraphic);
    void Draw() override;
    void Start() override;
    void Destroy() override;

    void ShowNext(int aBlockId, const std::string& aFrameId);

private:
    Text* m_NextText{nullptr};
    Transform* m_Transform{nullptr};
    Transform* m_AtlasTransform{nullptr};
    Atlas* m_BlockAtlas{ nullptr };

    Block m_BlockData;

    const int m_TileSize = 20;

    const std::string BLOCK_FRAME1 = "Block1";
    const std::string BLOCK_FRAME2 = "Block2";
    const std::string BLOCK_FRAME3 = "Block3";
    const std::string BLOCK_FRAME4 = "Block4";
    const std::string BLOCK_FRAME5 = "Block5";
    const std::string BLOCK_FRAME6 = "Block6";
    const std::string BLOCK_FRAME7 = "Block7";
    const std::string BLOCK_FRAME8 = "Block8";
    const std::string BLOCK_FRAME9 = "Block9";
};

#endif
