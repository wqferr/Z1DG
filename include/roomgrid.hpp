#ifndef D05E4F1E_C156_4E6B_8319_8340A0190F0A
#define D05E4F1E_C156_4E6B_8319_8340A0190F0A

namespace z1dg {
    class RoomGrid;
}

#include <cstddef>

#include "room.hpp"

namespace z1dg {
    class RoomGrid {
    public:
        RoomGrid(std::size_t rows, std::size_t cols, bool manage_room_destruction) noexcept;
        ~RoomGrid() noexcept;

        bool is_within_bounds(std::size_t row, std::size_t col) noexcept;
        bool has_room(std::size_t row, std::size_t col) noexcept;
        void add_room(std::size_t row, std::size_t col, Room *room);
        Room *get_room(std::size_t row, std::size_t col);
        // this doesnt make sense with the parent hierarchy set up in Room
        // bool remove_room(std::size_t row, std::size_t col);
    private:
        Room **elements;
        std::size_t n_rows, n_cols;
        bool manage_room_destruction;

        void check_oob(std::size_t row, std::size_t col);
    };
}

#endif/* D05E4F1E_C156_4E6B_8319_8340A0190F0A */
