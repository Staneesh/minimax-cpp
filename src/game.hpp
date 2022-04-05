#pragma once
#include <optional>
#include <initializer_list>

class Game
{
    char memory[9];

    Game();
    bool validate_position(unsigned position) const;
    int horizontal(unsigned start) const;
    int vertical(unsigned start) const;
    int diagonal(unsigned start) const;
    int aggregate_result(int result, std::initializer_list<int> temp) const;

public:
    enum Move
    {
        Player1 = 'x',
        Player2 = 'o',
        Empty = '_'
    };
    static std::optional<Game> init();
    bool make_a_move(unsigned position, Move m);
    int evaluate();
};