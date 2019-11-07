#include <StatsBox.h>
#include "Assets.h"

StatsBox::StatsBox()
{
    for (int i = 0; i < 7; i++)
    {
        m_BlockNumbers.push_back(new Text());
        m_BlockTextTransform.push_back(new Transform());
    }

    m_BlockAtlas = new Atlas();
    m_AtlasTransform = new Transform();

    m_StatsText = new Text();
    m_StatsTransform = new Transform();
}

void StatsBox::Draw()
{
    IGraphic& tGraphic = GetGraphics();

    tGraphic.SetColor(255, 255, 255, 255);

    m_StatsText->Draw();

    tGraphic.SetColor(190, 60, 0, 255);

    for (int i = 0; i < 7; i++)
    {
        m_BlockNumbers[i]->Draw();

        m_Block.SetBlock(i);

        vector<int> tData = m_Block.GetData(4);

        for (size_t j = 0; j < tData.size(); j++)
        {
            const int tValue = tData[j];

            if (tValue == 1)
            {
                const int tY = j / 5;
                const int tX = j - (5 * tY);
                m_AtlasTransform->SetPosition(
                    static_cast<float>(tX * 12 + 50), static_cast<float>(tY * 12 + 95) + i * 60);

                m_BlockAtlas->Update(m_AtlasTransform, 0.0f);
                m_BlockAtlas->Draw();
            }
        }
    }

    tGraphic.SetColor(0, 0, 0, 255);
}

void StatsBox::Start()
{
    IGraphic& tGraphic = GetGraphics();

    for (int i = 0; i < 7; i++)
    {
        m_BlockNumbers[i]->Load(Assets::EIGHTBIT_WONDER_FONT, 10);
        m_BlockNumbers[i]->SetText("000");
        m_BlockTextTransform[i]->SetPosition(150.0f, i * 60.0f + 110.0f);
        m_BlockNumbers[i]->Update(m_BlockTextTransform[i], 0.0f);
    }

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
    m_AtlasTransform->SetWidth(static_cast<float>(12));
    m_AtlasTransform->SetHeight(static_cast<float>(12));
    m_BlockAtlas->Update(m_AtlasTransform, 0.0f);


    m_StatsText->Load(Assets::EIGHTBIT_WONDER_FONT, 10);
    m_StatsText->SetText("STATISTICS");
    m_StatsTransform->SetPosition(30.0f, 55.0f);
    m_StatsText->Update(m_StatsTransform, 0.0f);
}

void StatsBox::Destroy()
{
    IGraphic& tGraphic = GetGraphics();

    for (int i = 0; i < 7; i++)
    {
        m_BlockNumbers[i]->Unload();
        SAFE_DELETE(m_BlockNumbers[i]);
        SAFE_DELETE(m_BlockTextTransform[i]);
    }

    m_BlockNumbers.clear();
    m_BlockTextTransform.clear();

    m_BlockAtlas->Unload();
    m_StatsText->Unload();

    SAFE_DELETE(m_BlockAtlas);
    SAFE_DELETE(m_AtlasTransform);
    SAFE_DELETE(m_StatsText);
    SAFE_DELETE(m_StatsTransform);
}

void StatsBox::OnBlockPlaced(int aBlock)
{
    m_BlockCount[aBlock]++;

    string tText = "";

    if (m_BlockCount[aBlock] > 99)
    {
        tText = tText + std::to_string(m_BlockCount[aBlock]);
    }
    else if (m_BlockCount[aBlock] > 9)
    {
        tText = tText + "0" + std::to_string(m_BlockCount[aBlock]);
    }
    else
    {
        tText = tText + "00" + std::to_string(m_BlockCount[aBlock]);
    }

    m_BlockNumbers[aBlock]->SetText(tText);
}

void StatsBox::ColorChanged(int aColor)
{
    m_BlockAtlas->SetFrame(m_BlockFrame[aColor]);
}
