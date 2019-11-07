#include <NextBlockBox.h>
#include <iostream>
#include "Assets.h"

NextBlockBox::NextBlockBox()
{
    m_NextText = new Text();
    m_Transform = new Transform();
    m_BlockAtlas = new Atlas();
    m_AtlasTransform = new Transform();
}

void NextBlockBox::DrawNextBlock(IGraphic& aGraphic)
{
    std::vector<int> tData = m_BlockData.GetData(4);
    const int tBlockId = m_BlockData.GetBlock();

    for (size_t i = 0; i < tData.size(); i++)
    {
        const int tValue = tData[i];

        if (tValue == 1)
        {
            const int tY = i / 5;
            const int tX = i - (5 * tY);

            if (tBlockId == 0 || tBlockId == 1)
            {
                m_AtlasTransform->SetPosition(
                    static_cast<float>(tX * m_TileSize + 618), static_cast<float>(tY * m_TileSize + 280));
            }
            else
            {
                m_AtlasTransform->SetPosition(
                    static_cast<float>(tX * m_TileSize + 609), static_cast<float>(tY * m_TileSize + 280));
            }

            m_BlockAtlas->Update(m_AtlasTransform, 0.0f);
            m_BlockAtlas->Draw();
        }
    }
}

void NextBlockBox::Draw()
{
    IGraphic& tGraphic = GetGraphics();

    tGraphic.SetColor(255, 255, 255, 255);
    m_NextText->Draw();

    DrawNextBlock(tGraphic);

    tGraphic.SetColor(0, 0, 0, 255);
}

void NextBlockBox::Start()
{
    IGraphic& tGraphic = GetGraphics();

    m_NextText->Load(Assets::EIGHTBIT_WONDER_FONT, 10);
    m_NextText->SetText("NEXT");
    m_Transform->SetPosition(620, 263);
    m_NextText->Update(m_Transform, 0.0f);

    m_BlockAtlas->Load(Assets::BLOCK_ATLAS);
    m_BlockAtlas->AddFrame(BLOCK_FRAME1, 0, 0, 114, 114);
    m_BlockAtlas->AddFrame(BLOCK_FRAME2, 114, 0, 114, 114);
    m_BlockAtlas->AddFrame(BLOCK_FRAME3, 228, 0, 114, 114);
    m_BlockAtlas->AddFrame(BLOCK_FRAME4, 342, 0, 114, 114);
    m_BlockAtlas->AddFrame(BLOCK_FRAME5, 456, 0, 114, 114);
    m_BlockAtlas->AddFrame(BLOCK_FRAME6, 570, 0, 114, 114);
    m_BlockAtlas->AddFrame(BLOCK_FRAME7, 684, 0, 114, 114);
    m_BlockAtlas->AddFrame(BLOCK_FRAME8, 798, 0, 114, 114);
    m_BlockAtlas->AddFrame(BLOCK_FRAME9, 912, 0, 114, 114);
    m_BlockAtlas->SetFrame(BLOCK_FRAME1);
    m_AtlasTransform->SetWidth(static_cast<float>(m_TileSize));
    m_AtlasTransform->SetHeight(static_cast<float>(m_TileSize));
    m_BlockAtlas->Update(m_AtlasTransform, 0.0f);
}

void NextBlockBox::Destroy()
{
    IGraphic& tGraphic = GetGraphics();

    m_BlockAtlas->Unload();
    m_NextText->Unload();

    SAFE_DELETE(m_NextText);
    SAFE_DELETE(m_Transform);
    SAFE_DELETE(m_BlockAtlas);
    SAFE_DELETE(m_AtlasTransform);
}

void NextBlockBox::ShowNext(const int aBlockId, const std::string& aFrameId)
{
    m_BlockData.SetBlock(aBlockId);
    m_BlockAtlas->SetFrame(aFrameId);
}
