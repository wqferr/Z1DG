#ifndef DCBC1024_9FBB_4F21_8E86_1915A785B2A0
#define DCBC1024_9FBB_4F21_8E86_1915A785B2A0

#include <memory>
#include <vector>

#include "threading.hpp"

namespace z1dg {
    template<typename T>
    class FreeListAllocator {
        public:
            using value_type = T;
            using size_type = std::size_t;
            using pointer = T *;
            using const_pointer = const T *;
            using difference_type = typename std::pointer_traits<pointer>::difference_type;

            template<typename U>
            struct rebind {
                typedef FreeListAllocator<U> other;
            };

            FreeListAllocator(FreeListAllocator<T>::size_type max_pool_size=500) noexcept;
            ~FreeListAllocator(void) noexcept;

            void populate_pool(size_type n, size_type size) noexcept;

            FreeListAllocator<T>::pointer allocate(FreeListAllocator<T>::size_type n) noexcept;
            void deallocate(FreeListAllocator<T>::pointer p, FreeListAllocator<T>::size_type n) noexcept;

        private:
            struct Block {
                pointer address;
                size_type n;

                Block(pointer address, size_type n): address(address), n(n) {}
                bool operator< (const Block &other) const {
                    return this->n < other.n;
                }
            };
            std::vector<Block> pool;
            size_type max_pool_size;
            mutex_type pool_mutex;
    };

    template<typename T>
    FreeListAllocator<T>::FreeListAllocator(FreeListAllocator<T>::size_type max_pool_size) noexcept
            : max_pool_size(max_pool_size) {
        create_mutex(this->pool_mutex);
    }

    template<typename T>
    FreeListAllocator<T>::~FreeListAllocator(void) noexcept {
        for (auto it = this->pool.begin(); it != this->pool.end(); it++) {
            free(it->address);
        }
    }

    template<typename T>
    void FreeListAllocator<T>::populate_pool(
            FreeListAllocator<T>::size_type n,
            FreeListAllocator<T>::size_type size) noexcept {
        lock_mutex(
            this->pool_mutex,
            [&](void *) {
                this->pool.reserve(this->pool.size() + n);
                for (size_type i = 0; i < n; i++) {
                    auto ptr = static_cast<pointer>(
                        malloc(size * sizeof(FreeListAllocator<T>::value_type))
                    );
                    this->pool.emplace_back(ptr, size);
                }
                return 0;
            }
        );
    }

    template<typename T>
    typename FreeListAllocator<T>::pointer FreeListAllocator<T>::allocate(FreeListAllocator<T>::size_type n) noexcept {
        if (this->pool.size() > 0) {
            Block b(nullptr, n);
            auto first_geq = std::lower_bound(this->pool.begin(), this->pool.end(), b);
            if (first_geq != this->pool.end()) {
                auto addr = first_geq->address;
                this->pool.erase(first_geq);
                return addr;
            }
        }
        return static_cast<pointer>(malloc(n * sizeof(value_type)));
    }

    template<typename T>
    void FreeListAllocator<T>::deallocate(FreeListAllocator<T>::pointer p, FreeListAllocator<T>::size_type n) noexcept {
        if (this->pool.size() >= this->max_pool_size) {
            free(p);
            return;
        }
        Block b(p, n);
        {
            lock_mutex(this->pool_mutex, [&](void *) {
                auto first_geq = std::lower_bound(this->pool.begin(), this->pool.end(), b);
                this->pool.insert(first_geq, b);
                return 0;
            });
        }
    }
}

#endif/* DCBC1024_9FBB_4F21_8E86_1915A785B2A0 */
