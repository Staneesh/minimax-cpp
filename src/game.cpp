#include "game.hpp"
#include <iostream>
#include <cmath>

unsigned Game::MAX_SUPPORTED_DEPTH = 10;

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
        // std::cerr << "Warning: Game::make_a_move will not make a move because spot nonempty!" << std::endl;
        return false;
    }

    *element = m;

    return true;
}

Game::Game(unsigned depth)
{
    this->depth = depth;
    for (unsigned i = 0; i < 9; ++i)
    {
        memory[i] = Move::Empty;
    }
}

std::optional<Game> Game::init(unsigned depth)
{
    if (depth < 1 || depth > Game::MAX_SUPPORTED_DEPTH)
        return std::nullopt;
    return Game(depth);
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

int Game::aggregate_result(int result, int temp) const
{
    if (abs(temp) > abs(result))
        result = temp;

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
            result = aggregate_result(result, horizontal);
        }
        if (starting_position < 3)
        {
            int vertical = this->vertical(starting_position);
            result = aggregate_result(result, vertical);
        }
        if (starting_position == 0 || starting_position == 3)
        {
            int diagonal = this->diagonal(starting_position);
            result = aggregate_result(result, diagonal);
        }
    }
    return result;
}

unsigned Game::empty_spaces() const
{
    unsigned result = 0;
    for (unsigned i = 0; i < 9; ++i)
    {
        if (this->memory[i] == Move::Empty)
        {
            result++;
        }
    }
    return result;
}

std::pair<unsigned, int> Game::predict_next_move(unsigned current_depth, Move active_player, unsigned previous_move)
{
    int current_score = this->evaluate();

    if (abs(current_score) == 3)
    {
        std::cerr << "abs(current_score) == 3, returning {" << previous_move << ", " << current_score << "}..." << std::endl;
        return {previous_move, current_score};
    }

    if (this->empty_spaces() == 0)
    {
        std::cerr << "No more room for a move, returning {" << previous_move << ", " << current_score << "}..." << std::endl;
        return {previous_move, current_score};
    }

    if (this->depth == current_depth)
    {
        std::cerr << "Max depth reached, returning {" << previous_move << ", " << current_score << "}..." << std::endl;
        return {previous_move, current_score};
    }

    if (active_player == Move::Player1)
    {
        int score_to_maximize = -10;
        unsigned winning_position = 13;

        for (unsigned i = 1; i < 10; ++i)
        {
            if (make_a_move(i, Move::Player1))
            {
                std::cerr << "Player 1 made a move on position " << i << std::endl;
                auto after_move = predict_next_move(current_depth + 1, Move::Player2, i);
                std::cerr << "after_move.first = " << after_move.first << " after_move.second = " << after_move.second << std::endl;
                if (after_move.second > score_to_maximize)
                {
                    score_to_maximize = after_move.second;
                    winning_position = after_move.first;
                }
                make_a_move(i, Move::Empty);
            }
        }

        std::cerr << "returning { " << winning_position << ", " << score_to_maximize << " }..." << std::endl;
        return {winning_position, score_to_maximize};
    }
    else
    {
        int score_to_minimize = 10;
        unsigned winning_position = 13;

        for (unsigned i = 1; i < 10; ++i)
        {
            if (make_a_move(i, Move::Player2))
            {
                std::cerr << "Player 2 made a move on position " << i << std::endl;
                auto after_move = predict_next_move(current_depth + 1, Move::Player1, i);
                std::cerr << "after_move.first = " << after_move.first << " after_move.second = " << after_move.second << std::endl;
                if (after_move.second < score_to_minimize)
                {
                    score_to_minimize = after_move.second;
                    winning_position = after_move.first;
                }
                make_a_move(i, Move::Empty);
            }
        }

        std::cerr << "returning { " << winning_position << ", " << score_to_minimize << " }..." << std::endl;
        return {winning_position, score_to_minimize};
    }
}