from cpython.mem cimport PyMem_Malloc, PyMem_Free
cimport cython

cdef class KeyItem:
    def __cinit__(self, bint consumable=False):
        self.consumable = consumable

@cython.freelist(500)
cdef class Room:
    def __cinit__(self, roomid id, KeyItem item=None):
        self.id = id
        self.item = item

        self.east = None
        self.west = None
        self.south = None
        self.north = None
        self.basement = None

    cdef void place_east_of(self, Room reference, KeyItem key=None) noexcept:
        reference.east = Door(self, key)
        self.west = Door(reference, key)

    cdef void place_west_of(self, Room reference, KeyItem key=None) noexcept:
        reference.west = Door(self, key)
        self.east = Door(reference, key)

    cdef void place_south_of(self, Room reference, KeyItem key=None) noexcept:
        reference.south = Door(self, key)
        self.north = Door(reference, key)

    cdef void place_north_of(self, Room reference, KeyItem key=None) noexcept:
        reference.north = Door(self, key)
        self.south = Door(reference, key)

    cdef void remove_basement(self) noexcept:
        self.basement = None

    cdef void make_tunnel_to(self, Room other_room) noexcept:
        basement = Basement(self)
        self.basement = basement
        other_room.basement = basement

        basement.exit1 = self
        basement.exit2 = other_room

    cdef void make_item_basement(self, KeyItem item) noexcept:
        self.basement = Basement(self, item)


@cython.freelist(100)
cdef class Basement:
    def __cinit__(self, Room room_above, KeyItem item=None):
        self.exit1 = room_above
        self.exit2 = None
        self.item = item

@cython.freelist(2000)
cdef class Door:
    def __cinit__(self, Room destination, KeyItem key=None):
        self.destination = destination
        self.key = key