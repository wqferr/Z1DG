ctypedef int direction

cdef enum Direction:
    NORTH = 0
    EAST = 1
    SOUTH = 2
    WEST = 3
#
# cdef inverse_directions = [
#     Direction.SOUTH,
#     Direction.WEST,
#     Direction.NORTH,
#     Direction.EAST,
# ]
#
# cdef direction_offsets = [
#     (0, 1),
#     (1, 0),
#     (-1, 0),
#     (0, -1)
# ]