cdef extern from "allocators/PoolAllocator.hpp" namespace "z1dg":
    cdef cppclass PoolAllocator:
        PoolAllocator(int total_size) except +
        ~PoolAllocator()
        void Init(void)
        void Reset(void)
        # cython doesn't need to know about these
        # void *Allocate(int size, int alignment=0)
        # void Free(void *ptr)