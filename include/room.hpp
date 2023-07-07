#ifndef A1D038E5_45DE_4CB8_9B65_A0A57477F6C1
#define A1D038E5_45DE_4CB8_9B65_A0A57477F6C1

#include "direction.hpp"
#include "item.hpp"
#include "except.hpp"

#include "allocators/PoolAllocator.hpp"

#include "roomgrid.hpp"

#include <tuple>
#include <list>

#define N_ROOMS_ALLOCATOR (70)

namespace z1dg {
    typedef unsigned int roomid;

    class Basement;
    class Room {
        private:
            RoomGrid *grid;
            Room *parent;
            std::list<Room *> children;
            Basement *basement;
            itemid lock;
            roomid id;
            int x, y;
            // bool is_root; check for depth == 0 instead
            int depth;

            static int get_next_id() {
                thread_local static int next_id = 1;
                return next_id++;
            }

            Room(RoomGrid *grid, int x, int y, int depth);
        public:
            static Room *make_root(RoomGrid *grid, int x, int y) noexcept;
            Room *make_child_adjacent(Direction direction);
            // TODO make_child_tunnel

            bool is_root() noexcept;
            roomid get_id() noexcept;
            int get_x() noexcept;
            int get_y() noexcept;

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

    class Basement {};
}


#endif/* A1D038E5_45DE_4CB8_9B65_A0A57477F6C1 */
