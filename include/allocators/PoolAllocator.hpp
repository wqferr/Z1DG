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

#ifndef C221C765_31D4_4E4C_A004_CD0263C93E94
#define C221C765_31D4_4E4C_A004_CD0263C93E94

#include "allocators/Allocator.hpp"
#include "allocators/StackLinkedList.hpp"

#include "threading.hpp"

namespace z1dg {
    class PoolAllocator : public Allocator {
    private:
        struct  FreeHeader{
        };
        using Node = StackLinkedList<FreeHeader>::Node;
        StackLinkedList<FreeHeader> m_freeList;

        void * m_start_ptr = nullptr;
        std::size_t m_chunkSize;
        z1dg::threading::mutex_type m_mutex;
    public:
        PoolAllocator(const std::size_t totalSize, const std::size_t chunkSize);

        virtual ~PoolAllocator();

        virtual void* Allocate(const std::size_t size, const std::size_t alignment = 0) override;

        virtual void Free(void* ptr) override;

        virtual void Init() override;

        virtual void Reset();
    private:
        PoolAllocator(PoolAllocator &poolAllocator);

    };
}

#endif/* C221C765_31D4_4E4C_A004_CD0263C93E94 */
