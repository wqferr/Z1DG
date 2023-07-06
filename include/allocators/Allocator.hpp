#ifndef E488462A_CCD4_48EF_9F5B_15F6F6594403
#define E488462A_CCD4_48EF_9F5B_15F6F6594403

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

#include <cstddef> // size_t

namespace z1dg::allocators {
    class Allocator {
    protected:
        std::size_t m_totalSize;
        std::size_t m_used;
        std::size_t m_peak;
    public:

        Allocator(const std::size_t totalSize) : m_totalSize { totalSize }, m_used { 0 }, m_peak { 0 } { }

        virtual ~Allocator() { m_totalSize = 0; }

        virtual void* Allocate(const std::size_t size, const std::size_t alignment = 0) = 0;

        virtual void Free(void* ptr) = 0;

        virtual void Init() = 0;

        friend class Benchmark;
    };
}

#endif/* E488462A_CCD4_48EF_9F5B_15F6F6594403 */