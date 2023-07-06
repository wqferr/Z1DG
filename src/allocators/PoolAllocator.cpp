/*
MIT License

Copyright (c) 2016 Mariano Trebino

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "allocators/PoolAllocator.hpp"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>     /* malloc, free */
#include <algorithm>    //max
#ifdef _DEBUG
#include <iostream>
#endif

namespace z1dg::allocators {
    PoolAllocator::PoolAllocator(const std::size_t totalSize, const std::size_t chunkSize)
    : Allocator(totalSize) {
        assert(chunkSize >= 8 && "Chunk size must be greater or equal to 8");
        assert(totalSize % chunkSize == 0 && "Total Size must be a multiple of Chunk Size");
        this->m_chunkSize = chunkSize;
        z1dg::threading::create_mutex(&this->m_mutex);
    }

    void PoolAllocator::Init() {
        m_start_ptr = malloc(m_totalSize);
        this->Reset();
    }

    PoolAllocator::~PoolAllocator() {
        free(m_start_ptr);
    }

    struct poolallocator_allocate_threadsafe {
        PoolAllocator *alloc;
        void *free_position;
    };

    void *PoolAllocator::Allocate(const std::size_t allocationSize, const std::size_t alignment) {
        assert(allocationSize == this->m_chunkSize && "Allocation size must be equal to chunk size");

        poolallocator_allocate_threadsafe arg { this, nullptr };
        z1dg::threading::lock_mutex(
            this->m_mutex,
            [](void *aptr) -> z1dg::threading::thread_return_status {
                poolallocator_allocate_threadsafe *a = static_cast<poolallocator_allocate_threadsafe *>(aptr);
                Node * freePosition = a->alloc->m_freeList.pop();

                assert(freePosition != nullptr && "The pool allocator is full");

                a->alloc->m_used += a->alloc->m_chunkSize;
                a->alloc->m_peak = std::max(a->alloc->m_peak, a->alloc->m_used);
                a->free_position = static_cast<void *>(freePosition);
            }
        );
#ifdef _DEBUG
        std::cout << "A" << "\t@S " << m_start_ptr << "\t@R " << (void*) arg.free_position << "\tM " << m_used << std::endl;
#endif

        return arg.free_position;
    }

    struct poolallocator_free_threadsafe {
        PoolAllocator *alloc;
        void *freed_ptr;
    };

    void PoolAllocator::Free(void * ptr) {
        poolallocator_free_threadsafe arg { this, ptr };
        z1dg::threading::lock_mutex(
            this->m_mutex,
            [](void *aptr) -> z1dg::threading::thread_return_status {
                poolallocator_free_threadsafe *a = static_cast<poolallocator_free_threadsafe *>(aptr);
                a->alloc->m_used -= a->alloc->m_chunkSize;
                a->alloc->m_freeList.push((Node *) a->freed_ptr);
            },
            &arg
        );

#ifdef _DEBUG
        std::cout << "F" << "\t@S " << m_start_ptr << "\t@F " << ptr << "\tM " << m_used << std::endl;
#endif
    }

    void PoolAllocator::Reset() {
        z1dg::threading::lock_mutex(
            m_mutex,
            [](void *ptr) -> z1dg::threading::thread_return_status {
                PoolAllocator *alloc = static_cast<PoolAllocator *>(ptr);
                alloc->m_used = 0;
                alloc->m_peak = 0;

                // Create a linked-list with all free positions
                const int nChunks = alloc->m_totalSize / alloc->m_chunkSize;
                for (int i = 0; i < nChunks; ++i) {
                    std::size_t address = (std::size_t) alloc->m_start_ptr + i * alloc->m_chunkSize;
                    alloc->m_freeList.push((Node *) address);
                }
                return 0;
            },
            this
        );
    }
}