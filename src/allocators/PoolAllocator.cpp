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
#include "format.hpp"

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>     /* malloc, free */
#include <algorithm>    //max

namespace z1dg {
    PoolAllocator::PoolAllocator(std::size_t nChunks, std::size_t chunkSize) {
        assert(chunkSize >= sizeof(Node) && format("Chunk size must be greater or equal to {}", sizeof(Node)).c_str());
        this->m_totalSize = nChunks * chunkSize;
        this->m_chunkSize = chunkSize;
    }

    void PoolAllocator::Init() {
        m_start_ptr = malloc(m_totalSize);
        this->Reset();
    }

    PoolAllocator::~PoolAllocator() {
        free(m_start_ptr);
    }

    void *PoolAllocator::Allocate() {
        Node * freePosition = this->m_freeList.pop();
        assert(freePosition != nullptr && "The pool allocator is full");

        return static_cast<void *>(freePosition);
    }

    std::size_t PoolAllocator::GetChunkSize(void) {
        return this->m_chunkSize;
    }

    void PoolAllocator::Free(void * ptr) {
        this->m_freeList.push((Node *) ptr);
    }

    void PoolAllocator::Reset() {
        // Create a linked-list with all free positions
        const int nChunks = this->m_totalSize / this->m_chunkSize;
        for (int i = 0; i < nChunks; ++i) {
            std::size_t address = (std::size_t) this->m_start_ptr + i * this->m_chunkSize;
            this->m_freeList.push((Node *) address);
        }
    }
}