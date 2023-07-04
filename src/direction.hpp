#ifndef B1513F4F_1FB1_48DA_924E_7C88B9EA4A87
#define B1513F4F_1FB1_48DA_924E_7C88B9EA4A87

#include <utility>

enum Direction {
    NORTH,
    EAST,
    SOUTH,
    WEST,

    N_DIRECTIONS
};

const Direction inverse_directions[] = {
    SOUTH,
    WEST,
    NORTH,
    EAST,
};

const std::pair<int, int> direction_offsets[] = {
    std::make_pair(0, 1),
    std::make_pair(1, 0),
    std::make_pair(0, -1),
    std::make_pair(-1, 0),
};

const char *direction_names[] = {
    "North",
    "East",
    "South",
    "West",
};

#endif /* B1513F4F_1FB1_48DA_924E_7C88B9EA4A87 */
