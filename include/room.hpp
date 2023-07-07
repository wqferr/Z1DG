#ifndef A1D038E5_45DE_4CB8_9B65_A0A57477F6C1
#define A1D038E5_45DE_4CB8_9B65_A0A57477F6C1

#include "direction.hpp"
#include "item.hpp"
#include "except.hpp"

#include "allocators/PoolAllocator.hpp"

#include <tuple>

#define N_ROOMS_ALLOCATOR (70)

namespace z1dg {
    typedef int roomid;

    class Basement;
    class Room {
        private:
            Direction parent_dir;
            Room *neighbors[N_DIRECTIONS];
            Basement *basement;
            itemid lock;
            roomid id;
            int x, y;
            bool is_root;
            int depth;

            static int get_next_id() {
                static int next_id = 0;
                return next_id++;
            }

            Room(int x, int y, int depth);
        public:
            static bool set_allocator(PoolAllocator *new_allocator);

            static Room *make_root(int x, int y) noexcept;

            Room *make_child(Direction direction);
            Room *get_parent();

            std::tuple<Room *, Room *, Room *> get_children();
            bool has_room_for_children();

            bool has_room_for_child(Direction direction);
            void set_lock(itemid required_key);
        };

    class Basement {};
}


#endif/* A1D038E5_45DE_4CB8_9B65_A0A57477F6C1 */
