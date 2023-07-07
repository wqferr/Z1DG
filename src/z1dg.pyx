from room cimport Room
from direction cimport Direction
from roomgrid cimport RoomGrid

cpdef test():
    cdef RoomGrid *grid = new RoomGrid(10, 10, True)
    cdef Room *root = Room.make_root(grid, 3, 5)
    del root
    # cdef Room *r = Room.make_root(grid, 0, 0)
    # cdef Room *child = r.make_child(Direction.NORTH)
    # print(r.get_child(Direction.SOUTH) == NULL)