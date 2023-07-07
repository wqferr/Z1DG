from room cimport Room

cpdef test():
    cdef Room *r = Room.make_root(0, 0)
    # Room.make_root(0, 0)