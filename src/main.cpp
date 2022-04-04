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
    std::cout << minimax_tree.get_depth() << std::endl;
    return 0;
}