#include "game.hpp"
#include <iostream>

bool Game::validate_position(unsigned p) const
{
    return (p > 0 && p < 10);
}

bool Game::make_a_move(unsigned position, Move m)
{
    if (this->validate_position(position) == false)
    {
        std::cerr << "Warning: Game::make_a_move will not make a move because position invalid!" << std::endl;
        return false;
    }
    auto element = &this->memory[position - 1];
    if (*element != Move::Empty)
    {
        std::cerr << "Warning: Game::make_a_move will not make a move because spot nonempty!" << std::endl;
        return false;
    }

    *element = m;

    return true;
}

Game::Game()
{
    for (unsigned i = 0; i < 9; ++i)
    {
        memory[i] = Move::Empty;
    }
}

std::optional<Game> Game::init()
{
    return Game();
}

int Game::horizontal(unsigned start) const
{
    // one of 3 possibilities - start is either 0, 3, or 6.
    if (start % 3 != 0)
    {
        std::cerr << "Error: Game::horizontal will not evaluate a bad position! Exiting..." << std::endl;
        exit(1);
    }

    int score = 0;
    // checking for players' scores
    for (unsigned i = 0; i < 3; ++i)
    {
        const char current_element = memory[start + i];
        if (current_element == Move::Player1)
        {
            score += 1;
        }
        if (current_element == Move::Player2)
        {
            score -= 1;
        }
    }

    return score;

    /*
        if (what_at_start == what_next == what_after == Move::Empty)
        {
            return 0;
        }

        int left_result = 0; // starting from left side going right
        if (what_at_start != Move::Empty && what_next == what_at_start)
        {
            if (what_at_start == what_after)
            {
                // all 3 are nonempty and equal
                left_result = 3;
            }
            else
            {
                left_result = 2;
            }

            if (what_at_start == Move::Player2)
            {
                left_result *= -1;
            }
        }

        int right_result = 0; // starting from right side going left
        if (what_after != Move::Empty && what_next == what_after)
        {
            // know that cannot be same all 3
            right_result = 2;

            if (what_after == Move::Player2)
            {
                right_result *= -1;
            }
        }

        if (left_result == 0 && what_at_start != Move::Empty)
        {
            if (what_at_start == Move::Player1)
            {
                return 1;
            }
        }
    */
}

int Game::vertical(unsigned start) const
{
    // one of 3 possibilities - start is either 0, 1, or 2.
    if (start > 2)
    {
        std::cerr << "Error: Game::horizontal will not evaluate a bad position! Exiting..." << std::endl;
        exit(1);
    }

    int score = 0;
    // checking for players' scores
    for (unsigned i = 0; i < 3; ++i)
    {
        const char current_element = memory[i * 3 + start];
        if (current_element == Move::Player1)
        {
            score += 1;
        }
        if (current_element == Move::Player2)
        {
            score -= 1;
        }
    }

    return score;
}

int Game::diagonal(unsigned start) const
{
    // one of 2 possibilities - start is either 0 or 3.
    if (start != 0 && start != 3)
    {
        std::cerr << "Error: Game::horizontal will not evaluate a bad position! Exiting..." << std::endl;
        exit(1);
    }

    int score = 0;
    if (start == 0)
    {
        for (unsigned i = 0; i < 9; i += 4) // 0, 4, 8
        {
            const char current_element = memory[start + i];
            if (current_element == Move::Player1)
            {
                score += 1;
            }
            if (current_element == Move::Player2)
            {
                score -= 1;
            }
        }
    }
    else // start == 3
    {
        for (unsigned i = 2; i < 7; i += 2) // 2, 4, 6
        {
            const char current_element = memory[start + i];
            if (current_element == Move::Player1)
            {
                score += 1;
            }
            if (current_element == Move::Player2)
            {
                score -= 1;
            }
        }
    }

    return score;
}

int Game::aggregate_result(int result, std::initializer_list<int> temp) const
{
    for (auto &&e : temp) // loop through temporary results
    {
        if (abs(e) > abs(result))
            result = e;
    }

    return result;
}

int Game::evaluate()
{
    int result = 0;
    for (unsigned starting_position = 0; starting_position < 9; ++starting_position)
    {
        if (starting_position % 3 == 0)
        {
            int horizontal = this->horizontal(starting_position);
            result = aggregate_result(result, {horizontal});
        }
        if (starting_position < 3)
        {
            int vertical = this->vertical(starting_position);
            result = aggregate_result(result, {vertical});
        }
        if (starting_position == 0 || starting_position == 3)
        {
            int diagonal = this->diagonal(starting_position);
            result = aggregate_result(result, {diagonal});
        }
    }
    return result;
}