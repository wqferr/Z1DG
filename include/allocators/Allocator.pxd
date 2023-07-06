cdef extern from "allocators/Allocator.hpp" namespace "z1dg":
    cdef cppclass Allocator:
        Allocator(int total_size) except +
        ~Allocator()
        void Init(void)
        # cython doesn't need to know about these
        # void *Allocate(int size, int alignment=0)
        # void Free(void *ptr)