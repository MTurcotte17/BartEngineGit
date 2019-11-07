#include <LineBox.h>
#include "Assets.h"

LineBox::LineBox()
{
    m_LineText = new Text();
    m_Transform = new Transform();
}

void LineBox::Draw()
{
    IGraphic& tGraphic = GetGraphics();

    tGraphic.SetColor(255, 255, 255, 255);
    m_LineText->Draw();

    tGraphic.SetColor(0, 0, 0, 255);
}

void LineBox::Start()
{
    IGraphic& tGraphic = GetGraphics();

    m_LineCount = 0;
    
    m_LineText->Load(Assets::EIGHTBIT_WONDER_FONT, 10);
    m_LineText->SetText("LINES - 000");
    m_Transform->SetPosition(318, 42);
    m_LineText->Update(m_Transform, 0.0f);
}

void LineBox::Destroy()
{
    IGraphic& tGraphic = GetGraphics();

    m_LineText->Unload();

    SAFE_DELETE(m_LineText);
    SAFE_DELETE(m_Transform);
}

void LineBox::OnLineClear(int aCount)
{
    m_LineCount += aCount;

    string tText = "LINES - ";

    if(m_LineCount > 99)
    {
        tText = tText + std::to_string(m_LineCount);
    }
    else if(m_LineCount > 9)
    {
        tText = tText + "0" + std::to_string(m_LineCount);
    }
    else
    {
        tText = tText + "00" + std::to_string(m_LineCount);
    }

    m_LineText->SetText(tText);
}
