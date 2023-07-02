from room cimport KeyItem, Room

cdef KeyItem SMALL_KEY = KeyItem(True)
cdef KeyItem BOW = KeyItem()

cpdef test():
    cdef Room entrance = Room(1, SMALL_KEY)
    cdef Room second_room = Room(2)
    second_room.make_item_basement(BOW)

    second_room.place_north_of(entrance, SMALL_KEY)
