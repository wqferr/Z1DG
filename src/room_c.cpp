#include "room.hpp"
#include "roomgrid.hpp"
#include "except.hpp"

#include <string>
#include <tuple>
#include <sstream>

#ifdef _DEBUG
#include <iostream>
#endif

namespace z1dg {
    thread_local PoolAllocator room_allocator(N_ROOMS_ALLOCATOR, sizeof(Room));

    Room *allocate_room(void) {
        return (Room *) room_allocator.Allocate();
    }

    void *Room::operator new(std::size_t nbytes) {
        (void) nbytes;
#ifdef _DEBUG
        std::cout << "allocated!" << std::endl;
#endif
        Room *new_room = static_cast<Room *>(room_allocator.Allocate());
        new_room->allocator = &room_allocator;
        return new_room;
    }

    void Room::operator delete(void *ptr) {
#ifdef _DEBUG
        std::cout << "deallocated!" << std::endl;
#endif

        static_cast<Room *>(ptr)->allocator->Free(ptr);
    }

    Room::Room(RoomGrid *grid, std::size_t row, std::size_t col, std::size_t depth): grid(grid), row(row), col(col), depth(depth) {
#ifdef _DEBUG
        std::cout << "constructor!" << std::endl;
#endif
        this->id = get_next_id();
        this->parent = nullptr;
        this->basement = nullptr;
        this->lock = NO_ITEM;

        grid->add_room(row, col, this);
    }

    bool Room::is_root() noexcept {
        return this->depth == 0;
    }

    roomid Room::get_id() noexcept {
        return this->id;
    }

    roomid Room::get_root_id() noexcept {
        return this->root_id;
    }

    std::size_t Room::get_row() noexcept {
        return this->row;
    }

    std::size_t Room::get_col() noexcept {
        return this->col;
    }

    Room *Room::make_root(RoomGrid *grid, std::size_t x, std::size_t y) noexcept {
        Room *root = new Room(grid, x, y, 0);
        root->root_id = root->id;
        return root;
    }

    Room *Room::make_child_adjacent(Direction direction) {
        if (!this->has_room_for_child(direction)) {
            std::stringstream ss("Space to the ");
            ss << direction_names[direction] << "of (";
            ss << static_cast<int>(this->row) << ", " << static_cast<int>(this->col);
            ss << ") is already occupied";
            throw DungeonGenException(ss.str().c_str());
        }

        auto dir_offset = direction_offsets[direction];
        Room *new_node = new Room(
            this->grid,
            this->row + dir_offset.first,
            this->col + dir_offset.second,
            this->depth + 1
        );
        new_node->parent = this;
        new_node->root_id = this->root_id;
        //this->children[direction] = new_node;

        return new_node;
    }

    Room *Room::get_parent() noexcept {
        return this->parent;
    }

    Room *Room::get_neighbor(Direction direction) noexcept {
        auto offset = direction_offsets[direction];
        return this->grid->get_room(
            this->row + std::get<0>(offset),
            this->col + std::get<1>(offset)
        );
    }

    std::tuple<int, int> Room::get_offset_from(Room *other) noexcept {
        return std::forward_as_tuple(
            this->row - other->row,
            this->col - other->col
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