#include "roomgrid.hpp"

#include <stdexcept>
#include <sstream>

namespace z1dg {
    RoomGrid::RoomGrid(std::size_t rows, std::size_t cols, bool delete_rooms_on_death) noexcept {
        this->elements = static_cast<Room **>(malloc(rows * cols * sizeof(*this->elements)));
        std::size_t total_rooms = rows * cols;
        for (std::size_t i = 0; i < total_rooms; i++) {
            this->elements[i] = nullptr;
        }
        this->delete_rooms_on_death = delete_rooms_on_death;
    }

    RoomGrid::~RoomGrid() noexcept {
        if (this->delete_rooms_on_death) {
            std::size_t total_rooms = this->n_rows * this->n_cols;
            for (std::size_t i = 0; i < total_rooms; i++) {
                if (this->elements[i] != nullptr) {
                    delete this->elements[i];
                }
            }
        }
        free(this->elements);
    }

    bool RoomGrid::is_within_bounds(std::size_t row, std::size_t col) noexcept {
        return row < this->n_rows && col < this->n_cols;
    }

    void RoomGrid::check_oob(std::size_t row, std::size_t col) {
        if (!this->is_within_bounds(row, col)) {
            std::stringstream ss("Position does not exist: ");
            ss << row << ", " << col;
            throw std::range_error(ss.str());
        }
    }

    bool RoomGrid::has_room(std::size_t row, std::size_t col) noexcept {
        return this->is_within_bounds(row, col) && this->get_room(row, col) != nullptr;
    }

    void RoomGrid::add_room(std::size_t row, std::size_t col, Room *room) {
        this->check_oob(row, col);
        auto index = row * this->n_cols + col;
        if (this->elements[index] != nullptr) {
            std::stringstream ss("Position is already occupied: ");
            ss << row << ", " << col;
            throw std::logic_error(ss.str());
        }
        this->elements[index] = room;
    }

    bool RoomGrid::remove_room(std::size_t row, std::size_t col) {
        this->check_oob(row, col);
        auto index = row * this->n_cols + col;
        bool success = this->elements[index] != nullptr;
        this->elements[index] = nullptr;
        return success;
    }

    Room *RoomGrid::get_room(std::size_t row, std::size_t col) {
        this->check_oob(row, col);
        return this->elements[row * this->n_cols + col];
    }
}