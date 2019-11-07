#include <ScoreBox.h>
#include "Assets.h"

ScoreBox::ScoreBox()
{
    m_ScoreText = new Text();
    m_ScoreValueText = new Text();
    m_ScoreTransform = new Transform();
    m_ScoreValueTransform = new Transform();
    m_LevelText = new Text();
    m_LevelValueText = new Text();
    m_LevelTransform = new Transform();
    m_LevelValueTransform = new Transform();

    m_NextText = new Text();
    m_NextTransform = new Transform();
    m_NextValueText = new Text();
    m_NextValueTransform = new Transform();
}

void ScoreBox::Draw()
{
    IGraphic& tGraphic = GetGraphics();

    tGraphic.SetColor(255, 255, 255, 255);
    m_ScoreText->Draw();
    m_ScoreValueText->Draw();
    m_LevelText->Draw();
    m_LevelValueText->Draw();
    m_NextText->Draw();
    m_NextValueText->Draw();

    tGraphic.SetColor(0, 0, 0, 255);
}

void ScoreBox::Start()
{
    IGraphic& tGraphic = GetGraphics();

    m_Score = 0;

    m_ScoreText->Load(Assets::EIGHTBIT_WONDER_FONT, 10);
    m_ScoreText->SetText("SCORE");
    m_ScoreTransform->SetPosition(620, 75);
    m_ScoreText->Update(m_ScoreTransform, 0.0f);

    m_ScoreValueText->Load(Assets::EIGHTBIT_WONDER_FONT, 10);
    m_ScoreValueText->SetText("0000000");
    m_ScoreValueTransform->SetPosition(620, 105);
    m_ScoreValueText->Update(m_ScoreValueTransform, 0.0f);

    m_LevelText->Load(Assets::EIGHTBIT_WONDER_FONT, 10);
    m_LevelText->SetText("LEVEL");
    m_LevelTransform->SetPosition(620, 408);
    m_LevelText->Update(m_LevelTransform, 0.0f);

    m_LevelValueText->Load(Assets::EIGHTBIT_WONDER_FONT, 10);
    m_LevelValueText->SetText("00");
    m_LevelValueTransform->SetPosition(660, 435);
    m_LevelValueText->Update(m_LevelValueTransform, 0.0f);

    m_NextText->Load(Assets::EIGHTBIT_WONDER_FONT, 10);
    m_NextText->SetText("NEXT");
    m_NextTransform->SetPosition(620, 145);
    m_NextText->Update(m_NextTransform, 0.0f);

    m_NextValueText->Load(Assets::EIGHTBIT_WONDER_FONT, 10);
    m_NextValueText->SetText("10");
    m_NextValueTransform->SetPosition(620, 175);
    m_NextValueText->Update(m_NextValueTransform, 0.0f);
}

void ScoreBox::Destroy()
{
    IGraphic& tGraphic = GetGraphics();

    m_ScoreText->Unload();
    m_ScoreValueText->Unload();
    m_LevelText->Unload();
    m_LevelValueText->Unload();
    m_NextText->Unload();
    m_NextValueText->Unload();

    SAFE_DELETE(m_ScoreText);
    SAFE_DELETE(m_ScoreValueText);
    SAFE_DELETE(m_ScoreTransform);
    SAFE_DELETE(m_ScoreValueTransform);
    SAFE_DELETE(m_LevelText);
    SAFE_DELETE(m_LevelValueText);
    SAFE_DELETE(m_LevelTransform);
    SAFE_DELETE(m_LevelValueTransform);
    SAFE_DELETE(m_NextText);
    SAFE_DELETE(m_NextTransform);
    SAFE_DELETE(m_NextValueText);
    SAFE_DELETE(m_NextValueTransform);
}

void ScoreBox::OnLineClear(int aCount, int aLevel)
{
    const int tScore = m_Scoring[aCount - 1] * (aLevel + 1);
    m_Score += tScore;

    int tZeroCount = 7;
    std::string tScoreTxt = std::to_string(m_Score);
    int tDiff = tZeroCount - tScoreTxt.length();
    std::string tScoreValueTxt = std::string(tDiff, '0') + tScoreTxt;
    m_ScoreValueText->SetText(tScoreValueTxt);
}

void ScoreBox::OnLevelUp(int aLevel, int aLineNeededForNext)
{
    m_Level = aLevel;

    int tZeroCount = 2;
    std::string tLevelTxt = std::to_string(aLevel);
    int tDiff = tZeroCount - tLevelTxt.length();
    std::string tLevelValue = std::string(tDiff, '0') + tLevelTxt;
    m_LevelValueText->SetText(tLevelValue);

    std::string tNextTxt = std::to_string(aLineNeededForNext);
    tDiff = tZeroCount - tNextTxt.length();
    std::string tNextValue = std::string(tDiff, '0') + tNextTxt;
    m_NextValueText->SetText(tNextValue);
}
