#include "minimax.hpp"
#include <iostream>

unsigned MinimaxTree::MAX_SUPPORTED_DEPTH = 10;

unsigned MinimaxTree::get_depth() const
{
    return this->depth;
}

MinimaxTree::MinimaxTree(unsigned depth) : depth(depth)
{
}

std::optional<MinimaxTree> MinimaxTree::init(unsigned depth)
{
    if (depth < 1 || depth > MinimaxTree::MAX_SUPPORTED_DEPTH)
        return std::nullopt;

    return MinimaxTree(depth);
}