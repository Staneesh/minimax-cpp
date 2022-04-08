#include <iostream>

#include "game.hpp"

int main()
{
    auto gm_opt = Game::init(2);
    if (!gm_opt.has_value())
    {
        std::cerr << "Error: Game::init() failed! Exiting..." << std::endl;
        return 1; // stanim: Error code
    }
    Game game = std::move(gm_opt.value());

    // std::cout << "INFO: Game state = " << game.evaluate() << std::endl;

    // game.make_a_move(1, Game::Move::Player1);

    // std::cout << "INFO: Game state = " << game.evaluate() << std::endl;

    // game.make_a_move(3, Game::Move::Player2);

    // std::cout << "INFO: Game state = " << game.evaluate() << std::endl;

    // auto prediction = game.predict_next_move(0, Game::Player1);

    // std::cout << "INFO: Predicting next move: " << prediction.first << " " << prediction.second << std::endl;

    while (game.evaluate() != 3 && game.empty_spaces() != 0)
    {
        int move;
        bool isMoveProper = false;
        while(!isMoveProper) {
            std::cout << "Make a move [1-9]" << std::endl;
            std::cin >> move;
            isMoveProper = game.make_a_move(move, Game::Move::Player1);
            system("CLS");
            game.print_memory();
        }

        if (game.evaluate() == 3)
        {
            std::cout << "Human wins!";
            break;
        }
        if (game.empty_spaces() == 0)
        {
            std::cout << "It is a draw. *yawn*";
            break;
        }

        game.print_memory();
        //std::cout << "INFO: Game state = " << game.evaluate() << std::endl;
        auto prediction = game.predict_next_move(0, Game::Player1);
        //std::cout << "PREDICITON {" << prediction.first << " " << prediction.second << "}" << std::endl;
        game.make_a_move(prediction.first, Game::Move::Player2);
        system("CLS");
        game.print_memory();
        if (game.evaluate() == -3) {
            std::cout << "AI wins!";
            break;
        }
    }

    // game.make_a_move(1, Game::Move::Player2);

    // std::cout << "INFO: Game state = " << game.evaluate() << std::endl;

    // game.make_a_move(5, Game::Move::Player2);

    // std::cout << "INFO: Game state = " << game.evaluate() << std::endl;

    // game.make_a_move(9, Game::Move::Player2);

    // std::cout << "INFO: Game state = " << game.evaluate() << std::endl;

    // auto prediction = game.predict_next_move(0, Game::Player1);

    // std::cout << "INFO: Predicting next move: " << prediction.first << " " << prediction.second << std::endl;

    return 0;
}