from room cimport Room
from direction cimport Direction
from roomgrid import RoomGrid

cpdef test():
    cdef RoomGrid *grid = new RoomGrid(10, 10)
    cdef Room *r = Room.make_root(0, 0)
    cdef Room *child = r.make_child(Direction.NORTH)
    print(r.get_child(Direction.SOUTH) == NULL)