#pragma once
#include <optional>

class Game
{
    static unsigned MAX_SUPPORTED_DEPTH;
    char memory[9];
    unsigned depth;

    Game(unsigned depth);
    bool validate_position(unsigned position) const;
    int horizontal(unsigned start) const;
    int vertical(unsigned start) const;
    int diagonal(unsigned start) const;
    int aggregate_result(int result, int temp) const;

public:
    enum Move
    {
        Player1 = 'x',
        Player2 = 'o',
        Empty = '_'
    };
    static std::optional<Game> init(unsigned depth);
    bool make_a_move(unsigned position, Move m);
    int evaluate();
    unsigned empty_spaces() const;

    // returns a pair of position+score
    std::pair<unsigned, int> predict_next_move(unsigned current_depth = 0, Move active_player = Move::Player1, unsigned previous_move = 13, int alpha = -10, unsigned beta = 10);
};