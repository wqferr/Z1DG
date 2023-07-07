#ifndef B1513F4F_1FB1_48DA_924E_7C88B9EA4A87
#define B1513F4F_1FB1_48DA_924E_7C88B9EA4A87

#include <utility>

namespace z1dg {
    typedef int Direction;
    const Direction NORTH = 0;
    const Direction EAST = 1;
    const Direction SOUTH = 2;
    const Direction WEST = 3;

    const Direction N_DIRECTIONS = 4;

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
}

#endif /* B1513F4F_1FB1_48DA_924E_7C88B9EA4A87 */
