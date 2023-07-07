from room cimport Room

cdef extern from "roomgrid.cpp":
    pass

cdef extern from "roomgrid.hpp" namespace "z1dg":
    cdef cppclass RoomGrid "z1dg::RoomGrid":
        RoomGrid(int, int, bint)
        ~RoomGrid()

        bool is_within_bounds(int row, int col)
        bool has_room(int row, int col)
        void add_room(int row, int col, Room *room);
        Room *get_room(int row, int col);
        bool remove_room(int row, int col);