#pragma once
#include <optional>
#include <vector>

class MinimaxTree
{
private:
    static unsigned MAX_SUPPORTED_DEPTH;

    unsigned depth;

    MinimaxTree(unsigned depth);

public:
    unsigned get_depth() const;

    static std::optional<MinimaxTree> init(unsigned depth);
};