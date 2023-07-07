cdef extern from "room.cpp":
    pass

cdef extern from "room.hpp" namespace "z1dg":
    cdef cppclass Room "Room":
        @staticmethod
        Room *make_root(int x, int y)