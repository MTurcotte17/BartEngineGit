#include <Board.h>
#include <BoardControl.h>
#include <iostream>
#include <MathHelper.h>
#include <Assets.h>

Board::Board()
{
    const unsigned tSeed = static_cast<unsigned>(Engine::Instance().GetTimer().GetTime());
    MathHelper::SetSeed(tSeed);

    m_BoardSize = m_BoardHeight * m_BoardWidth;

    const size_t tByteSize = m_BoardSize * sizeof(int);
    m_Board = static_cast<int*>(std::malloc(tByteSize));
    std::memset(m_Board, BLOCK_NONE, tByteSize);

    m_BoardControl = new BoardControl();
    m_BlockAtlas = new Atlas();
    m_Transform = new Transform();
    m_GameOverText = new Text();
    m_BackToMenuText = new Text();

    m_FallSound = new Sound();
    m_RotateSound = new Sound();
    m_MoveSound = new Sound();
    m_LineRemove1 = new Sound();
    m_LineRemove4 = new Sound();
    m_LevelUpSound = new Sound();

    m_GameOverTransform = new Transform();
    m_BackToMenuTransform = new Transform();
}

void Board::Draw()
{
    IGraphic& tGraphic = GetGraphics();

    DrawBoard(tGraphic);

    if (!m_Playing)
    {
        tGraphic.SetColor(255, 255, 255, 255);
        m_GameOverText->Draw();
        m_BackToMenuText->Draw();
    }

    tGraphic.SetColor(0, 0, 0, 255);
}

void Board::ClearBlock(const int aValue)
{
    vector<int> tBlockData = m_CurrentBlock.GetData(m_Rotation);
    const int tBlockSize = m_CurrentBlock.GetSize();

    for (size_t i = 0; i < tBlockData.size(); i++)
    {
        if (tBlockData[i] == BLOCK_TILE)
        {
            int tX, tY;
            GetLocalPosition(i, tBlockSize, &tX, &tY);
            const int tIdx = FromBlockToBoard(tX, tY, m_X, m_Y, m_BoardWidth);

            if (tIdx < static_cast<int>(m_BoardSize) && tIdx >= 0)
            {
                m_Board[tIdx] = aValue;
            }
        }
    }
}

void Board::ChooseNextBlock()
{
    m_CurrentBlock.SetBlock(m_NextBlock);
    m_NextBlock = m_CurrentBlock.RandomBlock(false);

    if (tNextBlockEntity != nullptr)
    {
        tNextBlockEntity->ShowNext(m_NextBlock, m_BlockFrames[m_CurrentColor]);
    }
}

void Board::Fall()
{
    ClearBlock(0);

    if (CheckCollision(m_X, m_Y + 1, m_Rotation))
    {
        Place();
    }
    else
    {
        m_Y += 1;
        ClearBlock(1);
    }
}

void Board::Place()
{
    m_FallSound->Play(0);

    if (m_StatsBox != nullptr)
    {
        m_StatsBox->OnBlockPlaced(m_CurrentBlock.GetBlock());
    }

    ClearBlock(2);
    CheckLines();

    if (m_Y < 0)
    {
        m_Playing = false;
        m_ClearY = m_BoardHeight - 1;
        if (m_GameScreen != nullptr)
        {
            m_GameScreen->OnGameOver();
        }
    }
    else
    {
        SpawnNextBlock();
        NormalFall();
    }
}

void Board::SpawnNextBlock()
{
    ChooseNextBlock();
    m_X = MathHelper::RandomRange(0, m_BoardWidth - 5);
    m_Y = START_Y;
    m_Rotation = 0;
}

void Board::GetLocalPosition(const int aIndex, const int aGridWidth, int* aCol, int* aRow) const
{
    *aRow = aIndex / aGridWidth;
    *aCol = aIndex - (aGridWidth * (*aRow));
}

void Board::GetWorldPosition(const int aIndex, int* aX, int* aY) const
{
    GetLocalPosition(aIndex, m_BoardWidth, aX, aY);
    *aX *= m_TileSize;
    *aY *= m_TileSize;
}

int Board::GetIndexFromPosition(const int aX, const int aY, const int aWidth) const
{
    return aX + aWidth * aY;
}

int Board::FromBlockToBoard(const int aBlkX, const int aBlkY, const int aBrdX, const int aBrdY, const int aGrdW) const
{
    return GetIndexFromPosition(aBrdX + aBlkX, aBrdY + aBlkY, aGrdW);
}

void Board::RemoveLine(const int aRow) const
{
    for (unsigned i = 0; i < m_BoardWidth; i++)
    {
        const int tIdx = GetIndexFromPosition(i, aRow, m_BoardWidth);
        m_Board[tIdx] = BLOCK_NONE;
    }
}

void Board::AddLines(int aCount)
{
    m_TotalLines += aCount;
    if (m_TotalLines >= m_LineForNextLevel)
    {
        m_Level++;
        m_LevelUpSound->Play(0);

        m_NormalDelay = MathHelper::Clamp(m_NormalDelay - 0.2f, 0.0f, 1.0f);
        m_CurrentColor = MathHelper::Rotation(m_CurrentColor + 1, 1, static_cast<int>(m_BlockFrames.size()));
        m_LineForNextLevel = m_Level * 10 + 10;

        if (tScoreBox != nullptr)
        {
            tScoreBox->OnLevelUp(m_Level, m_LineForNextLevel);
        }

        if (m_GameScreen != nullptr)
        {
            m_GameScreen->OnLevelChange(m_Level);
        }

        if (m_StatsBox != nullptr)
        {
            m_StatsBox->ColorChanged(m_CurrentColor);
        }
    }
}

void Board::ScrollBoard(int aRow, const vector<int>& aRemovedLines)
{
    if (tLineBox != nullptr)
    {
        const int tLineCount = static_cast<int>(aRemovedLines.size());

        AddLines(tLineCount);
        tLineBox->OnLineClear(tLineCount);
        tScoreBox->OnLineClear(tLineCount, m_Level);
    }

    for (size_t i = 0; i < aRemovedLines.size(); i++)
    {
        for (int y = aRemovedLines[i]; y >= 0; y--)
        {
            for (unsigned x = 0; x < m_BoardWidth; x++)
            {
                const int tIdxA = GetIndexFromPosition(x, y, m_BoardWidth);
                const int tIdxB = GetIndexFromPosition(x, y + 1, m_BoardWidth);

                if (m_Board[tIdxA] == PLACED_TILE && m_Board[tIdxB] == BLOCK_NONE)
                {
                    m_Board[tIdxA] = BLOCK_NONE;
                    m_Board[tIdxB] = PLACED_TILE;
                }
            }
        }
    }
}

void Board::CheckLines()
{
    bool tLineComplete = false;
    int tLineRemoved = 0;
    int tCurrIdx = 0;
    int tY = -1;
    vector<int> tLinesRemoved;

    for (unsigned y = 0; y < m_BoardHeight; y++)
    {
        tLineComplete = true;
        for (unsigned x = 0; x < m_BoardWidth; x++)
        {
            tCurrIdx = GetIndexFromPosition(x, y, m_BoardWidth);
            if (m_Board[tCurrIdx] != PLACED_TILE)
            {
                tLineComplete = false;
                break;
            }
        }

        if (tLineComplete)
        {
            if (tY < 0)
            {
                tY = y;
            }

            tLinesRemoved.push_back(y);
            RemoveLine(y);
            tLineRemoved++;
        }
    }

    if (tLineRemoved > 0)
    {
        ScrollBoard(tY, tLinesRemoved);

        if (tLineRemoved >= 4)
        {
            m_LineRemove4->Play(0);
        }
        else
        {
            m_LineRemove1->Play(0);
        }
    }
}

bool Board::CheckCollision(const int aX, const int aY, const int aRotation)
{
    vector<int> tData = m_CurrentBlock.GetData(aRotation);
    const int tBlockSize = m_CurrentBlock.GetSize();

    for (size_t i = 0; i < tData.size(); i++)
    {
        if (tData[i] == BLOCK_TILE)
        {
            int tX, tY;
            GetLocalPosition(i, tBlockSize, &tX, &tY);
            const int tIdx = FromBlockToBoard(tX, tY, aX, aY, m_BoardWidth);

            if (tIdx >= 0)
            {
                const unsigned tNewX = aX + tX;
                if (tIdx >= static_cast<int>(m_BoardSize) || tNewX > m_BoardWidth - 1 || tNewX < 0 || m_Board[tIdx] ==
                    PLACED_TILE)
                {
                    return true;
                }
            }
            else
            {
                return true;
            }
        }
    }

    return false;
}

void Board::Translate(const int aDirection)
{
    const int tX = m_X + aDirection;

    if (!CheckCollision(tX, m_Y, m_Rotation))
    {
        m_MoveSound->Play(0);
        ClearBlock(BLOCK_NONE);
        m_X = tX;
        ClearBlock(BLOCK_TILE);
    }
}

void Board::Rotate()
{
    const int tRotation = m_CurrentBlock.NextRotation(m_Rotation);
    if (!CheckCollision(m_X, m_Y, tRotation))
    {
        m_RotateSound->Play(0);
        ClearBlock(BLOCK_NONE);
        m_Rotation = tRotation;
        ClearBlock(BLOCK_TILE);
    }
}

void Board::FastFall()
{
    if (m_Delay != m_FastDelay)
    {
        m_Delay = m_FastDelay;

        if (m_GameScreen != nullptr)
        {
            m_GameScreen->OnFallSpeedChange(m_Delay);
        }
    }
}

void Board::NormalFall()
{
    if (m_Delay != m_NormalDelay)
    {
        m_Delay = m_NormalDelay;

        if (m_GameScreen != nullptr)
        {
            m_GameScreen->OnFallSpeedChange(m_Delay);
        }
    }
}

void Board::Start()
{
    IGraphic& tGraphic = GetGraphics();

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
    m_BlockAtlas->AddFrame(PLACED_FRAME, 1026, 0, 114, 114);
    m_BlockAtlas->AddFrame(GRID_FRAME, 1140, 0, 114, 114);
    m_BlockAtlas->AddFrame(GAMEOVER_FRAME, 1254, 0, 114, 114);

    SpawnNextBlock();

    m_Level = 0;
    m_TotalLines = 0;
    m_LineForNextLevel = m_Level * 10 + 10;
    m_CurrentColor = 0;

    tNextBlockEntity = static_cast<NextBlockBox*>(Engine::Instance().GetScene().FindEntity("NextBlockBox"));
    tLineBox = static_cast<LineBox*>(Engine::Instance().GetScene().FindEntity("LineBox"));
    tScoreBox = static_cast<ScoreBox*>(Engine::Instance().GetScene().FindEntity("ScoreBox"));
    m_GameScreen = static_cast<GameScreen*>(Engine::Instance().GetScene().FindEntity("GameScreen"));
    m_StatsBox = static_cast<StatsBox*>(Engine::Instance().GetScene().FindEntity("StatsBox"));

    m_NextBlock = m_CurrentBlock.RandomBlock(true);
    ChooseNextBlock();
    NormalFall();

    m_Transform->SetWidth(static_cast<float>(m_TileSize));
    m_Transform->SetHeight(static_cast<float>(m_TileSize));

    m_FallSound->Load(Assets::BLOCK_HIT_SOUND);
    m_RotateSound->Load(Assets::BLOCK_ROTATION_SOUND);
    m_MoveSound->Load(Assets::BLOCK_MOVE_SOUND);
    m_LineRemove1->Load(Assets::ONE_LINE_REMOVED_SOUND);
    m_LineRemove4->Load(Assets::FOUR_LINES_REMOVED_SOUND);
    m_LevelUpSound->Load(Assets::LEVEL_UP_SOUND);

    m_GameOverText->Load(Assets::EIGHTBIT_WONDER_FONT, 12);
    m_GameOverText->SetText("GAME OVER");
    m_GameOverTransform->SetPosition(320.0f, 300.0f);
    m_GameOverText->Update(m_GameOverTransform, 0.0f);

    m_BackToMenuText->Load(Assets::EIGHTBIT_WONDER_FONT, 12);
    m_BackToMenuText->SetText("Press esc");
    m_BackToMenuTransform->SetPosition(320.0f, 340.0f);
    m_BackToMenuText->Update(m_BackToMenuTransform, 0.0f);

    m_Playing = true;
}

void Board::Update(float aDeltaTime)
{
    m_Elapsed += aDeltaTime;

    m_BoardControl->Update(*this, aDeltaTime);

    if (m_Playing)
    {
        if (m_Elapsed >= m_Delay)
        {
            m_Elapsed = 0.0f;
            Fall();
        }
    }
    else
    {
        if (m_Elapsed >= 0.1f)
        {
            m_Elapsed = 0.0f;
            for (unsigned x = 0; x < m_BoardWidth; x++)
            {
                const int tIdx = GetIndexFromPosition(x, m_ClearY, m_BoardWidth);
                m_Board[tIdx] = GAME_OVER_TILE;
            }

            if (m_ClearY > 0)
            {
                m_ClearY--;
            }
        }
    }
}

void Board::DrawTile(IGraphic& aGraphic, const std::string& aName, const int aX, const int aY) const
{
    m_Transform->SetPosition(static_cast<float>(aX + m_BoardPosX), static_cast<float>(aY + m_BoardPosY));
    m_BlockAtlas->Update(m_Transform, 0.0f);
    m_BlockAtlas->SetFrame(aName);
    m_BlockAtlas->Draw();
}

void Board::DrawBoard(IGraphic& aGraphic)
{
    int tX, tY;

    for (size_t i = 0; i < m_BoardSize; i++)
    {
        GetWorldPosition(i, &tX, &tY);
        if (m_Board[i] == BLOCK_TILE)
        {
            DrawTile(aGraphic, m_BlockFrames[m_CurrentColor], tX, tY);
        }
        else if (m_Board[i] == PLACED_TILE)
        {
            DrawTile(aGraphic, m_BlockFrames[m_CurrentColor], tX, tY);
        }
        else if (m_Board[i] == GAME_OVER_TILE)
        {
            DrawTile(aGraphic, GAMEOVER_FRAME, tX, tY);
        }
    }
}

void Board::DrawGameOver(IGraphic& aGraphic) const
{
    int tX, tY;

    for (size_t i = 0; i < m_BoardSize; i++)
    {
        GetWorldPosition(i, &tX, &tY);
        DrawTile(aGraphic, GAMEOVER_FRAME, tX, tY);
    }
}

void Board::Destroy()
{
    IGraphic& tGraphic = GetGraphics();

    m_BlockAtlas->Unload();
    m_GameOverText->Unload();
    m_BackToMenuText->Unload();
    m_FallSound->Unload();
    m_RotateSound->Unload();
    m_MoveSound->Unload();
    m_LineRemove1->Unload();
    m_LineRemove4->Unload();
    m_LevelUpSound->Unload();

    SAFE_DELETE(m_BoardControl);
    SAFE_DELETE(m_BlockAtlas);
    SAFE_DELETE(m_Transform);
    SAFE_DELETE(m_GameOverText);
    SAFE_DELETE(m_BackToMenuText);
    SAFE_DELETE(m_FallSound);
    SAFE_DELETE(m_RotateSound);
    SAFE_DELETE(m_MoveSound);
    SAFE_DELETE(m_LineRemove1);
    SAFE_DELETE(m_LineRemove4);
    SAFE_DELETE(m_LevelUpSound);
    SAFE_DELETE(m_GameOverTransform);
    SAFE_DELETE(m_BackToMenuTransform);

    free(m_Board);
}
