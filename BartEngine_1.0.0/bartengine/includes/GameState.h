#ifndef BART_GAME_STATE_H
#define BART_GAME_STATE_H

namespace bart
{
    class GameState
    {
    public:
        virtual ~GameState() = default;

        virtual void Load() = 0;
    };
}

#endif
