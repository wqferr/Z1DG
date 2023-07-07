from room cimport Room

cdef extern from "roomgrid_c.cpp":
    pass

cdef extern from "roomgrid.hpp" namespace "z1dg":
    cdef cppclass RoomGrid "z1dg::RoomGrid":
        RoomGrid(int n_rows, int n_cols, bint manage_room_deletion) except +

        bint is_within_bounds(int row, int col)
        bint has_room(int row, int col)
        void add_room(int row, int col, Room *room)
        Room *get_room(int row, int col)
        bint remove_room(int row, int col)