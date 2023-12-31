#ifndef A1D038E5_45DE_4CB8_9B65_A0A57477F6C1
#define A1D038E5_45DE_4CB8_9B65_A0A57477F6C1

namespace z1dg {
    class Room;
}

#include "direction.hpp"
#include "item.hpp"
#include "except.hpp"

#include "allocators/PoolAllocator.hpp"

#include "roomgrid.hpp"
#include "allocators/PoolAllocator.hpp"

#include <tuple>
#include <list>

#define N_ROOMS_ALLOCATOR (200)

namespace z1dg {
    typedef unsigned int roomid;

    class Basement;
    class Room {
        private:
            PoolAllocator *allocator;
            RoomGrid *grid;
            Room *parent;
            std::list<Room *> children;
            Basement *basement;
            itemid lock;
            roomid id, root_id;
            std::size_t row, col;
            std::size_t depth;

            static int get_next_id() {
                thread_local static int next_id = 1;
                return next_id++;
            }

            Room(RoomGrid *grid, std::size_t row, std::size_t col, std::size_t depth);
        public:
            static Room *make_root(RoomGrid *grid, std::size_t row, std::size_t col) noexcept;
            Room *make_child_adjacent(Direction direction);
            Room *make_child_tunnel(std::size_t row, std::size_t col);

            void add_item_basement(itemid item);

            bool is_root() noexcept;
            roomid get_id() noexcept;
            roomid get_root_id() noexcept;
            std::size_t get_row() noexcept;
            std::size_t get_col() noexcept;

            Room *get_parent() noexcept;
            Room *get_neighbor(Direction direction) noexcept;

            std::tuple<int, int> get_offset_from(Room *other) noexcept;
            std::list<Room *> get_children() noexcept;
            bool has_room_for_children() noexcept;

            bool has_room_for_child(Direction direction) noexcept;
            void set_lock(itemid required_key) noexcept;

            void *operator new(std::size_t nbytes);
            void operator delete(void *ptr);
        };

    class Basement {
    private:
        Room *parent;
        Room *child;
        itemid item;
    };
}


#endif/* A1D038E5_45DE_4CB8_9B65_A0A57477F6C1 */
