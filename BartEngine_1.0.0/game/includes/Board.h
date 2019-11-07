#ifndef BOARD_H
#define BOARD_H

#include <Entity.h>
#include <vector>
#include <Block.h>
#include <Atlas.h>
#include <Sound.h>
#include <Text.h>
#include <NextBlockBox.h>
#include <LineBox.h>
#include <ScoreBox.h>
#include <GameScreen.h>
#include <StatsBox.h>

using namespace bart;

class BoardControl;

class Board final : public Entity
{
public:
    virtual ~Board() = default;
    Board();
    bool CanDraw() override { return true; }
    bool CanUpdate() override { return true; }
    void Draw() override;
    void Start() override;
    void Update(float aDeltaTime) override;
    void Destroy() override;
    void Translate(int aDirection);
    void Rotate();
    void FastFall();
    void NormalFall();

private:
    void DrawTile(IGraphic& aGraphic, const std::string& aName, int aX, int aY) const;
    void DrawBoard(IGraphic& aGraphic);
    void DrawGameOver(IGraphic& aGraphic) const;
    void GetWorldPosition(int aIndex, int* aX, int* aY) const;
    void GetLocalPosition(int aIndex, int aGridWidth, int* aCol, int* aRow) const;
    void ClearBlock(int aValue);
    void ChooseNextBlock();
    void Fall();
    bool CheckCollision(int aX, int aY, int aRotation);
    void Place();
    void SpawnNextBlock();
    int FromBlockToBoard(int aBlkX, int aBlkY, int aBrdX, int aBrdY, int aGrdW) const;
    int GetIndexFromPosition(int aX, int aY, int aWidth) const;

    void CheckLines();
    void RemoveLine(int aRow) const;
    void AddLines(int aCount);
    void ScrollBoard(int aRow, const vector<int>& aRemovedLines);

    BoardControl* m_BoardControl{nullptr};
    Atlas* m_BlockAtlas{nullptr};
    Transform* m_Transform{nullptr};
    Transform* m_GameOverTransform{nullptr};
    Transform* m_BackToMenuTransform{nullptr};
    Sound* m_FallSound{nullptr};
    Sound* m_RotateSound{nullptr};
    Sound* m_MoveSound{nullptr};
    Sound* m_LineRemove1{nullptr};
    Sound* m_LineRemove4{nullptr};
    Sound* m_LevelUpSound{nullptr};
    Text* m_GameOverText{ nullptr };
    Text* m_BackToMenuText{nullptr};

    NextBlockBox* tNextBlockEntity;
    LineBox* tLineBox;
    ScoreBox* tScoreBox;
    GameScreen* m_GameScreen;
    StatsBox* m_StatsBox;

    int* m_Board;
    int m_TileSize{20};
    unsigned m_BoardWidth{13};
    unsigned m_BoardHeight{22};
    unsigned m_BoardSize{0};
    int m_BoardPosX{296};
    int m_BoardPosY{102};
    float m_Delay{0.0f};
    float m_Elapsed{0.0f};
    float m_FastDelay{0.0f};
    float m_NormalDelay{1.0f};
    const int BLOCK_NONE = 0;
    const int BLOCK_TILE = 1;
    const int PLACED_TILE = 2;
    const int GAME_OVER_TILE = 3;

    const int START_Y = -2;
    
    const std::string BLOCK_FRAME1 = "Block1";
    const std::string BLOCK_FRAME2 = "Block2";
    const std::string BLOCK_FRAME3 = "Block3";
    const std::string BLOCK_FRAME4 = "Block4";
    const std::string BLOCK_FRAME5 = "Block5";
    const std::string BLOCK_FRAME6 = "Block6";
    const std::string BLOCK_FRAME7 = "Block7";
    const std::string BLOCK_FRAME8 = "Block8";
    const std::string BLOCK_FRAME9 = "Block9";

    vector<std::string> m_BlockFrames =
    {
        BLOCK_FRAME1, 
        BLOCK_FRAME2, 
        BLOCK_FRAME3, 
        BLOCK_FRAME4, 
        BLOCK_FRAME5, 
        BLOCK_FRAME6, 
        BLOCK_FRAME7, 
        BLOCK_FRAME8, 
        BLOCK_FRAME9, 
    };

    const std::string PLACED_FRAME = "Placed";
    const std::string GRID_FRAME = "Grid";
    const std::string GAMEOVER_FRAME = "GameOver";

    Block m_CurrentBlock;
    int m_X{0};
    int m_Y{0};
    int m_Rotation;
    int m_NextBlock;
    bool m_Playing{true};
    int m_ClearY{0};
    int m_Level{0};
    int m_CurrentColor{0};
    int m_TotalLines{0};
    int m_LineForNextLevel{0};
};

#endif
