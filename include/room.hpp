#include "direction.hpp"
#include "item.hpp"
#include "except.hpp"

#include "allocators/Allocator.hpp"

#include <tuple>

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

            static z1dg::Allocator *allocator;

            static int get_next_id() {
                static int next_id = 0;
                return next_id++;
            }

            static Room *allocate();
            Room(int x, int y, int depth);
        public:
            static void set_allocator(z1dg::Allocator *new_allocator);

            static Room *make_root(
                    int x,
                    int y,
                    float prob_children=1.0f,
                    float prob_single_child=0.3f,
                    int max_depth=9,
                    int n_tunnels=1,
                    int n_item_rooms=1) noexcept;

            Room *make_child(Direction direction);
            Room *get_parent();

            std::tuple<Room *, Room *, Room *> get_children();
            bool has_room_for_children();

            bool has_room_for_child(Direction direction);
            void set_lock(itemid required_key);
        };

    class Basement {};
}