#include <GamePlay.h>
#include <Engine.h>
#include <GameScreen.h>
#include <Board.h>
#include <NextBlockBox.h>
#include <LineBox.h>
#include <ScoreBox.h>
#include <StatsBox.h>

void GamePlay::Load()
{
    Engine::Instance().GetScene().AddEntity("GameScreen", new GameScreen());
    Engine::Instance().GetScene().AddEntity("Board", new Board());
    Engine::Instance().GetScene().AddEntity("NextBlockBox", new NextBlockBox());
    Engine::Instance().GetScene().AddEntity("LineBox", new LineBox());
    Engine::Instance().GetScene().AddEntity("ScoreBox", new ScoreBox());
    Engine::Instance().GetScene().AddEntity("StatsBox", new StatsBox());
}
