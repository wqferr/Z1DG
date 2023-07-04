ctypedef int roomid
cdef roomid NO_ROOM = -1

cdef class KeyItem:
    cdef bint consumable

cdef class Room:
    cdef:
        roomid id

        # direction order is the same as in TLoZ
        Door east
        Door west
        Door south
        Door north

        Basement basement
        KeyItem item

        void place_east_of(self, Room reference, KeyItem key=?) noexcept
        void place_west_of(self, Room reference, KeyItem key=?) noexcept
        void place_south_of(self, Room reference, KeyItem key=?) noexcept
        void place_north_of(self, Room reference, KeyItem key=?) noexcept
        void remove_basement(self) noexcept
        void make_tunnel_to(self, Room other_room) noexcept
        void make_item_basement(self, KeyItem item) noexcept

cdef class Basement:
    cdef Room exit1
    cdef Room exit2
    cdef KeyItem item

cdef class Door:
    cdef:
        KeyItem key
        Room destination
