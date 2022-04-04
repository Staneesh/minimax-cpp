#pragma once

class Game
{
    enum Move
    {
        Player1 = 'x',
        Player2 = 'o',
        Empty = '_'
    };
    std::vector<char> memory;

public:
    bool make_a_move(unsigned position, Move m);
    int evaluate();
};