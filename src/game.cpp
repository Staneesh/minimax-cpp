#include "game.hpp"
#include <iostream>

bool Game::make_a_move(unsigned position, Move m)
{
    if (position != Move::Empty)
    {
        std::cerr << "Warning: Game::make_a_move will not make a move because spot nonempty!" << std::endl;
        return false;
    }

        return true;
}