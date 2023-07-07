from direction import Direction
from roomgrid cimport RoomGrid

cdef extern from "room_c.cpp":
    pass

cdef extern from "room.hpp" namespace "z1dg":
    cdef cppclass Room "z1dg::Room":
        @staticmethod
        Room *make_root(RoomGrid *grid, int x, int y)

        Room *make_child_adjacent(int direction) # "make_child_adjacent"
        Room *get_neighbor(int direction) # "get_child"

        (int, int) get_offset_from(Room *other) # "get_offset_from"