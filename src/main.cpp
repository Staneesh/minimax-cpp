#include <iostream>

#include "minimax.hpp"
#include "game.hpp"

int main()
{
    auto mt_opt = MinimaxTree::init(3);
    if (!mt_opt.has_value())
    {
        std::cerr << "Error: MinimaxTree::init() failed! Exiting..." << std::endl;
        return 1; // stanim: Error code
    }
    MinimaxTree minimax_tree = std::move(mt_opt.value());

    auto gm_opt = Game::init();
    if (!gm_opt.has_value())
    {
        std::cerr << "Error: Game::init() failed! Exiting..." << std::endl;
        return 1; // stanim: Error code
    }
    Game game = std::move(gm_opt.value());

    std::cout << "INFO: Game state = " << game.evaluate() << std::endl;

    game.make_a_move(3, Game::Move::Player1);

    std::cout << "INFO: Game state = " << game.evaluate() << std::endl;

    game.make_a_move(2, Game::Move::Player1);

    std::cout << "INFO: Game state = " << game.evaluate() << std::endl;

    game.make_a_move(1, Game::Move::Player2);

    std::cout << "INFO: Game state = " << game.evaluate() << std::endl;

    return 0;
}