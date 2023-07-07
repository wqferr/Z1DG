#include "room.hpp"
#include "roomgrid.hpp"
#include "except.hpp"

#include <string>
#include <tuple>

#include <iostream>

namespace z1dg {

    thread_local PoolAllocator room_allocator(N_ROOMS_ALLOCATOR, sizeof(Room));

    Room *allocate_room(void) {
        return (Room *) room_allocator.Allocate();
    }
    void *Room::operator new(std::size_t nbytes) {
        (void) nbytes;
        std::cout << "allocated! " << nbytes << " vs " << sizeof(Room) << std::endl;
        return room_allocator.Allocate();
    }

    void Room::operator delete(void *ptr) {
        std::cout << "deallocated!";
        room_allocator.Free(ptr);
    }

    Room::Room(RoomGrid *grid, int x, int y, int depth): grid(grid), x(x), y(y), depth(depth) {
        this->id = get_next_id();
        this->parent = nullptr;
        this->basement = nullptr;
        this->lock = NO_ITEM;
    }

    bool Room::is_root() noexcept {
        return this->depth == 0;
    }

    roomid Room::get_id() noexcept {
        return this->id;
    }

    int Room::get_x() noexcept {
        return this->x;
    }

    int Room::get_y() noexcept {
        return this->y;
    }

    Room *Room::make_root(RoomGrid *grid, int x, int y) noexcept {
        // Room *root = allocate_room();
        // new (root) Room(grid, x, y, 0); // run constructor, but dont allocate memory
        return new Room(grid, x, y, 0);
    }

    Room *Room::make_child_adjacent(Direction direction) {
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
        // Room *new_node = allocate_room();
        // new (new_node) Room( // call constructor on already allocated memory
        Room *new_node = new Room(
            this->grid,
            this->x + dir_offset.first,
            this->y + dir_offset.second,
            this->depth + 1
        );
        new_node->parent = this;
        //this->children[direction] = new_node;

        return new_node;
    }

    Room *Room::get_parent() noexcept {
        return this->parent;
    }

    Room *Room::get_neighbor(Direction direction) noexcept {
        auto offset = direction_offsets[direction];
        return this->grid->get_room(
            this->x + std::get<0>(offset),
            this->y + std::get<1>(offset)
        );
    }

    std::tuple<int, int> Room::get_offset_from(Room *other) noexcept {
        return std::forward_as_tuple(
            this->x - other->x,
            this->y - other->y
        );
    }

    bool Room::has_room_for_child(Direction direction) noexcept {
        // TODO
        return false;
    }

    void Room::set_lock(itemid required_key) noexcept {
        this->lock = required_key;
    }
}