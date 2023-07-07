#ifndef D05E4F1E_C156_4E6B_8319_8340A0190F0A
#define D05E4F1E_C156_4E6B_8319_8340A0190F0A

#include <cstddef>

#include "room.hpp"

namespace z1dg {
    class Room;

    class RoomGrid {
    public:
        RoomGrid(std::size_t rows, std::size_t cols, bool delete_children_on_death) noexcept;
        ~RoomGrid() noexcept;
        bool is_within_bounds(std::size_t row, std::size_t col) noexcept;
        bool has_room(std::size_t row, std::size_t col) noexcept;
        void add_room(std::size_t row, std::size_t col, Room *room);
        Room *get_room(std::size_t row, std::size_t col);
        bool remove_room(std::size_t row, std::size_t col);
    private:
        Room **elements;
        std::size_t n_rows, n_cols;
        bool delete_rooms_on_death;

        void check_oob(std::size_t row, std::size_t col);
    };
}

#endif/* D05E4F1E_C156_4E6B_8319_8340A0190F0A */
