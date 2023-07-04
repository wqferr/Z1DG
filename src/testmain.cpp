#include "freelistallocator.hpp"

#include <cstdlib>
#include <vector>
#include <utility>
#include <algorithm>

#include <iostream>


int main(void) {
    using pairii = std::pair<int, int>;
    using alloc_type = z1dg::FreeListAllocator<pairii>;
    alloc_type alloc;
    using alloc_traits = std::allocator_traits<alloc_type>;
    const int N = 30;
    pairii *pairs[N];
    for (int i = 0; i < N; i++) {
        std::cout << i << std::endl;
        pairs[i] = alloc_traits::allocate(alloc, 1);
        alloc_traits::construct(alloc, pairs[i], i, i*i);
        if (i % 4 == 0) {
            alloc_traits::destroy(alloc, pairs[i]);
            alloc_traits::deallocate(alloc, pairs[i], 1);
            pairs[i] = nullptr;
        }
        if (i > 0 && i % 12 == 0) {
            for (int j = 0; j < 4; j++) {
                if (pairs[i-j] == nullptr) continue;
                alloc_traits::destroy(alloc, pairs[i-j]);
                alloc_traits::deallocate(alloc, pairs[i-j], 1);
                pairs[i-j] = nullptr;
            }
        }
    }
    return 0;
}