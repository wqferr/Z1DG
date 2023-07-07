#include "room.hpp"
#include "except.hpp"

#include <string>

namespace z1dg {

    thread_local PoolAllocator room_allocator(N_ROOMS_ALLOCATOR, sizeof(Room));

    Room *allocate(void) {
        return (Room *) room_allocator.Allocate();
    }

    Room::Room(int x, int y, int depth): x(x), y(y), depth(depth) {
        this->id = get_next_id();
        this->basement = nullptr;
        this->lock = NO_ITEM;
        this->is_root = false;
    }

    Room *Room::make_root(int x, int y) noexcept {
        Room *root = allocate();
        new (root) Room(x, y, 0); // run constructor, but dont allocate memory
        root->is_root = true;
        return root;
    }

    Room *Room::make_child(Direction direction) {
        if (!this->has_room_for_child(direction)) {
            std::string msg = "Space to the ";
            msg += direction_names[direction];
            msg += " of (";
            msg += this->x;
            msg += ", ";
            msg += this->y;
            msg += ") is already occupied";
            throw DungeonGenException(msg.c_str());
        }

        auto dir_offset = direction_offsets[direction];
        Room *new_node = allocate();
        new (new_node) Room( // call constructor on already allocated memory
            this->x + dir_offset.first,
            this->y + dir_offset.second,
            this->depth + 1
        );
        new_node->parent_dir = inverse_directions[direction];
        new_node->neighbors[new_node->parent_dir] = this;
        this->neighbors[direction] = new_node;

        return new_node;
    }

    Room *Room::get_parent() {
        if (this->is_root) {
            return nullptr;
        } else {
            return this->neighbors[this->parent_dir];
        }
    }

    std::tuple<Room *, Room *, Room *> Room::get_children() {
        return std::forward_as_tuple(
            this->neighbors[(this->parent_dir + 1) % N_DIRECTIONS],
            this->neighbors[(this->parent_dir + 2) % N_DIRECTIONS],
            this->neighbors[(this->parent_dir + 3) % N_DIRECTIONS]
        );
    }

    bool Room::has_room_for_children() {
        auto children = this->get_children();
        return std::get<0>(children) == nullptr
            || std::get<1>(children) == nullptr
            || std::get<2>(children) == nullptr;
    }

    bool Room::has_room_for_child(Direction direction) {
        return this->neighbors[direction] == nullptr;
    }

    void Room::set_lock(itemid required_key) {
        this->lock = required_key;
    }
}