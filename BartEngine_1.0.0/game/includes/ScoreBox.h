#ifndef SCORE_BOX_H
#define SCORE_BOX_H

#include <Entity.h>
#include <Text.h>

using namespace bart;

class ScoreBox final : public Entity
{
public:
    virtual ~ScoreBox() = default;
    ScoreBox();

    bool CanDraw() override { return true; }
    bool CanUpdate() override { return false; }
    void Draw() override;
    void Start() override;
    void Destroy() override;

    void OnLineClear(int aCount, int aLevel);
    void OnLevelUp(int aLevel, int aLineNeededForNext);

private:
    Text* m_ScoreText{nullptr};
    Transform* m_ScoreTransform{nullptr};

    Text* m_ScoreValueText{nullptr};
    Transform* m_ScoreValueTransform{nullptr};

    Text* m_LevelText{ nullptr };
    Transform* m_LevelTransform{ nullptr };

    Text* m_LevelValueText{ nullptr };
    Transform* m_LevelValueTransform{ nullptr };

    Text* m_NextText{ nullptr };
    Transform* m_NextTransform{ nullptr };

    Text* m_NextValueText{ nullptr };
    Transform* m_NextValueTransform{ nullptr };

    int m_Score{0};
    int m_Level{0};

    vector<int> m_Scoring = {40, 100, 300, 1200};
};

#endif
